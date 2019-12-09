#include "input_linux.h"

enum Linux_Key {
LINUX_KEY_SPACE          = 32,
LINUX_KEY_APOSTROPHE     = 39,
#if 0
asterisk             42
plus                 43
comma                44
minus                45
period               46
slash                47
0                    48
1                    49
2                    50
3                    51
4                    52
5                    53
6                    54
7                    55
8                    56
9                    57
colon                58
semicolon            59
less                 60
equal                61
greater              62
question             63
at                   64
bracketleft          91
backslash            92
bracketright         93
asciicircum          94
underscore           95
grave                96
a                    97
b                    98
c                    99
d                   100
e                   101
f                   102
g                   103
h                   104
i                   105
j                   106
k                   107
l                   108
m                   109
n                   110
o                   111
p                   112
q                   113
r                   114
s                   115
t                   116
u                   117
v                   118
w                   119
x                   120
y                   121
#endif
};

namespace Engine {

bool key_state[PLATFORM_KEY_COUNT] = {0};

} // end namespace Engine

