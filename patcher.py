import sys
import re

print "#pragma GCC diagnostic ignored \"-fpermissive\"" #(void* -> int* etc)
print "#include \"patch.hpp\""

for line in sys.stdin:
    line = line.replace("malloc","p_malloc")
    line = line.replace("free","p_free")
    line = line.replace("realloc","p_realloc")
    line = re.sub(r"([a-zA-Z]+)\w*\*",r"Ptr<\1> ",line)

    print line,