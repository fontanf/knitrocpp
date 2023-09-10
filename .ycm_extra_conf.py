import os

def Settings(**kwargs):
    return {
            'flags': [
                '-x', 'c++',
                '-Wall', '-Wextra', '-Werror',
                '-I', '.',

                # Knitro
                '-I', os.getenv('KNITRODIR') + '/include/',

                # CppAD
                '-I', './bazel-knitrocpp/external/cppad/include/'

                ],
            }
