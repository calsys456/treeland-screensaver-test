# treeland-screensaver-test

This repo provides a single executable which is aimed to test if the
`org.freedesktop.ScreenSaver` D-Bus interface works correct on
[Treeland](https://github.com/linuxdeepin/treeland).

## Usage

```bash
git clone https://github.com/calsys456/treeland-screensaver-test.git
cd treeland-screensaver-test
cmake -Bbuild .
cmake --build build
./build/treeland-screensaver-test
```

Sample output for successful test:

```
Connected to org.freedesktop.ScreenSaver.
Inhibit once. Cookie: 1
UnInhibit cookie 1
treeland-screensaver has exited as expected.
Inhibit once. Cookie: 1
Inhibit twice. Cookie: 2
UnInhibit cookie 1
Disconnecting from D-Bus to test automatic uninhibit...
treeland-screensaver has exited as expected.
Success.
```
