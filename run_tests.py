#!/usr/bin/env python3

'''Test module'''

import sys
import os

if __name__ == '__main__':
    DIRS = ['md5', 'sha256', 'sha224', 'sha512', 'sha384']
    PIDS = []
    S_OPT = False
    OPT = ""

    sys.argv = sys.argv[1:]
    for o in sys.argv[:2]:
        if S_OPT:
            try:
                OPT = int(o)
                if OPT < 1:
                    raise TypeError
                S_OPT = False
            except (TypeError, ValueError):
                print(f"""Error: Invalid size "{o}" """)
                sys.exit(1)
            sys.argv = sys.argv[2:]
        elif o == '-s':
            S_OPT = True

    for d in sys.argv if len(sys.argv) != 0 else DIRS:
        pid = os.fork()
        if pid != 0:
            PIDS.append(pid)
        else:
            if d not in DIRS:
                print(f"""Error: Can't find "{d}" tests""")
                sys.exit(1)
            else:
                os.system(f'cd {"srcs/algs/" + d}; make -s re')
                os.system(f'{"srcs/algs/" + d + "/" + d} {OPT}')
                os.system(f'cd {"srcs/algs/" + d}; make -s fclean')
                sys.exit(0)

    for pid in PIDS:
        os.waitpid(pid, 0)
