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
                sys.exit(os.system(f'make -s -C {d} re; ./{d}/{d}_test; make -s -C {d} fclean'))

    for pid in PIDS:
        os.waitpid(pid, 0)
