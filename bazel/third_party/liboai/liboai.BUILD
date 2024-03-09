package(
    default_visibility = ['//visibility:public'],
)

cc_library(
    name= 'oai',
    srcs = glob([
        'liboai/components/*.cpp',
        'liboai/core/*.cpp',
    ]),
    hdrs = ['.'],
    # hdrs = ['.'] + glob([
        # 'liboai/components/*.h',
        # 'liboai/core/*.h',
    # ]),
    # includes = [
        # '.',
        # 'liboai/',
        # 'liboai/components/',
        # 'liboai/core/',
    # ],
    deps = ['@com_github_nlohmann_json//:json'],
)

