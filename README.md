# linux_cp_command
Description:
------------
try to mimic linux cp command and try to achieve linux performance
1. testcp.c : will use stdio apis (read from source & write to destnation).
2. scaterGatherIO.c : will use readv() and writev() api
