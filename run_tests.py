#!/bin/env python3

'''Test module'''

import sys
import os

if __name__ == '__main__':
    DIRS = ['md5', 'sha256', 'sha224']
    PIDS = []

    for d in sys.argv[1:] if len(sys.argv) > 1 else DIRS:
        pid = os.fork()
        if pid != 0:
            PIDS.append(pid)
        else:
            if d not in DIRS:
                print(f"""Error: Can't find "{d}" tests""")
                sys.exit(1)
            else:
                os.system(f'make -s -C {d} re')
                os.system(f'./{d}/{d}_test')
                os.system(f'make -s -C {d} fclean')
                sys.exit(0)

    for pid in PIDS:
        os.waitpid(pid, 0)
