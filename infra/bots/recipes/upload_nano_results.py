# Copyright 2016 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.


# Recipe for uploading nanobench results.


DEPS = [
  'build/file',
  'recipe_engine/path',
  'recipe_engine/properties',
  'recipe_engine/step',
  'recipe_engine/time',
]


def RunSteps(api):
  # Upload the nanobench resuls.
  builder_name = api.properties['buildername']

  patch_storage = api.properties.get('patch_storage', 'rietveld')
  issue = None
  patchset = None
  if builder_name.endswith('-Trybot'):
    if patch_storage == 'gerrit':
      issue = str(api.properties['event.change.number'])
      patchset = str(api.properties['event.patchSet.ref'].split('/')[-1])
    else:
      issue = str(api.properties['issue'])
      patchset = str(api.properties['patchset'])

  now = api.time.utcnow()

  src_path = api.path['cwd'].join(
      'perfdata', builder_name, 'data')
  results = api.file.glob(
      'find results',
      'nanobench*.json',
      cwd=src_path,
      test_data=['nanobench_abc123.json'],
      infra_step=True)
  if len(results) != 1:  # pragma: nocover
    raise Exception('Unable to find nanobench JSON file!')

  src = src_path.join(results[0])
  basename = api.path.basename(src)
  gs_path = '/'.join((
      'nano-json-v1', str(now.year).zfill(4),
      str(now.month).zfill(2), str(now.day).zfill(2), str(now.hour).zfill(2),
      builder_name))

  if builder_name.endswith('-Trybot'):
    if not (issue and patchset):  # pragma: nocover
      raise Exception('issue and patchset properties are required for trybots.')
    gs_path = '/'.join(('trybot', gs_path, issue, patchset))

  dst = '/'.join(('gs://skia-perf', gs_path, basename))

  api.step('upload',
           cmd=['gsutil', 'cp', '-a', 'public-read', '-z', 'json', src, dst],
           infra_step=True)


def GenTests(api):
  builder = 'Test-Ubuntu-GCC-GCE-CPU-AVX2-x86_64-Debug'
  yield (
    api.test('normal_bot') +
    api.properties(buildername=builder,
                   revision='abc123',
                   path_config='kitchen')
  )

  builder = 'Test-Ubuntu-GCC-GCE-CPU-AVX2-x86_64-Debug-Trybot'
  yield (
    api.test('trybot') +
    api.properties(buildername=builder,
                   revision='abc123',
                   path_config='kitchen',
                   issue='12345',
                   patchset='1002')
  )

  gerrit_kwargs = {
    'patch_storage': 'gerrit',
    'repository': 'skia',
    'event.patchSet.ref': 'refs/changes/00/2100/2',
    'event.change.number': '2100',
  }
  yield (
      api.test('recipe_with_gerrit_patch') +
      api.properties(
          buildername=builder,
          revision='abc123',
          path_config='kitchen',
          **gerrit_kwargs)
  )
