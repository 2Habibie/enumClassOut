# If there is no version tag in git this one will be used
VERSION = 21.02.18

# Need to discard STDERR so get path to NULL device
win32 {
    NULL_DEVICE = NUL # Windows doesn't have /dev/null but has NUL
} else {
    NULL_DEVICE = /dev/null
}

# Need to call git with manually specified paths to repository
BASE_GIT_COMMAND = git --git-dir $$PWD/.git --work-tree $$PWD

# Trying to get version from git tag / revision
#GIT_VERSION = $$system($$BASE_GIT_COMMAND describe --abbrev=0 2> $$NULL_DEVICE)
#GIT_HASH = $$system($$BASE_GIT_COMMAND rev-parse -q HEAD 2> $$NULL_DEVICE)
GIT_VERSION = $$system($$BASE_GIT_COMMAND describe --always 2> $$NULL_DEVICE)
GIT_HASH = $$system($$BASE_GIT_COMMAND rev-parse --short -q HEAD 2> $$NULL_DEVICE)

# Now we are ready to pass parsed version to Qt
VERSION = $$GIT_VERSION
win32 { # On windows version can only be numerical so remove commit hash
    VERSION ~= s/\.\d+\.[a-f0-9]{6,}//
}

# Adding C preprocessor #DEFINE so we can use it in C++ code
# also here we want full version on every system so using GIT_VERSION
DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"
DEFINES += GIT_HASH=\\\"$$GIT_HASH\\\"

# By default Qt only uses major and minor version for Info.plist on Mac.
# This will rewrite Info.plist with full version
macx {
    INFO_PLIST_PATH = $$shell_quote($${OUT_PWD}/$${TARGET}.app/Contents/Info.plist)
    QMAKE_POST_LINK += /usr/libexec/PlistBuddy -c \"Set :CFBundleShortVersionString $${VERSION}\" $${INFO_PLIST_PATH}
}
