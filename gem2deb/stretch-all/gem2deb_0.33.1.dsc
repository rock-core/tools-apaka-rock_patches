Format: 3.0 (native)
Source: gem2deb
Binary: gem2deb, gem2deb-test-runner
Architecture: any
Version: 0.33.1
Maintainer: Debian Ruby Extras Maintainers <pkg-ruby-extras-maintainers@lists.alioth.debian.org>
Uploaders: Lucas Nussbaum <lucas@debian.org>, Antonio Terceiro <terceiro@debian.org>, Vincent Fourmond <fourmond@debian.org>, Gunnar Wolf <gwolf@debian.org>, Cédric Boutillier <boutil@debian.org>, Christian Hofstaedtler <zeha@debian.org>
Standards-Version: 3.9.8
Vcs-Browser: https://anonscm.debian.org/cgit/pkg-ruby-extras/gem2deb.git
Vcs-Git: https://anonscm.debian.org/git/pkg-ruby-extras/gem2deb.git
Testsuite: autopkgtest
Testsuite-Triggers: build-essential, fakeroot
Build-Depends: dctrl-tools <!nocheck>, debhelper (>= 9.20141010), devscripts <!nocheck>, dpkg-dev (>= 1.17.14), lintian <!nocheck>, python3-debian <!nocheck>, rake <!nocheck>, ruby (>= 1:2.1.0.3~), ruby-all-dev (>= 1:2.1.0.3~), ruby-mocha (>= 0.14.0) <!nocheck>, ruby-rspec <!nocheck>, ruby-setup <!nocheck>, ruby-shoulda-context <!nocheck>, ruby-test-unit <!nocheck>
Package-List:
 gem2deb deb ruby optional arch=any
 gem2deb-test-runner deb ruby optional arch=any
Checksums-Sha1:
 712d911f0334fcffa2cd5596aaeb40c6cab8ec81 66124 gem2deb_0.33.1.tar.xz
Checksums-Sha256:
 702815a2e058f758cc5134e8fd97cbf94d2efed9dc204d74095aa7f6bbadfcd3 66124 gem2deb_0.33.1.tar.xz
Files:
 31f08463c74b6155f6d9eaef06d7b8c0 66124 gem2deb_0.33.1.tar.xz
