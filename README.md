# apaka-rock_patches - Patches for the Rock Debian Package creation with apaka

This library contains a set of patches as basis for the creation of Debian
packages from Rock.
The patches intend to fix installation and integration issues,
and are not intending to introduce new features to a release.

## Usage / Testing
In order to test building of packages please bootstrap a standard Rock
workspace:

```
$ mkdir workspace
$ cd workspace
workspace$ wget https://www.rock-robotics.org/autoproj_bootstrap
workspace$ ruby autoproj_bootstrap
```

Then clone and build [apaka](https://github.com/rock-core/tools-apaka) into your
workspace

```
workspace$ source env.sh
workspace$ mkdir tools
workspace$ git clone https://github.com/rock-core/tools-apaka.git tools/apaka
```

Clone this repository:
```
workspace$ git clone https://github.com/rock-core/tools-apaka-rock_patches.git tools/apaka-rock_patches
```

Activate the package sets rock and rock.core, add your packages that should be
in the release and tools/apaka to autoproj/manifest:
```
package_sets:
    - github: rock-core/package_set
    - github: rock-core/rock-package_set

layout:
    - rock.core
    - tools/apaka
```

Now build and use apaka to prepare your system and build your release:
```
workspace$ autoproj osdeps
workspace$ amake tools/apaka
workspace$ source env.sh
workspace$ apaka --prepare
workspace$ apaka --patch-dir tools/apaka-rock_patches --release-name test
```

## Merge Request and Issue Tracking

Github will be used for pull requests and issue tracking: https://github.com/rock-core/apaka-rock_patches

## License

Patches are distributed under the [New/3-clause BSD license](https://opensource.org/licenses/BSD-3-Clause)

The gems concurrent-ruby and concurrent-ruby-ext are redistributed under their
original MIT license.

## Copyright

Copyright (c) 2014-2019, DFKI GmbH Robotics Innovation Center

