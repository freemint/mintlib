  /*   0 - E_OK */                 ERR(N_("Success"), 14)
  /*   1 - EERROR */               ERR(N_("Generic Error"), 22)
  /*   2 - EBUSY */                ERR(N_("Device or resource busy"), 36)
  /*   3 - EUKCMD */               ERR(N_("Unknown command"), 60)
  /*   4 - ECRC */                 ERR(N_("CRC error"), 76)
  /*   5 - EBADR */                ERR(N_("Invalid request descriptor"), 86)
  /*   6 - ESPIPE */               ERR(N_("Illegal seek"), 113)
  /*   7 - EMEDIUMTYPE */          ERR(N_("Wrong medium type"), 126)
  /*   8 - ESECTOR */              ERR(N_("Sector not found"), 144)
  /*   9 - EPAPER */               ERR(N_("Out of paper"), 161)
  /*  10 - EWRITE */               ERR(N_("Write fault"), 174)
  /*  11 - EREAD */                ERR(N_("Read fault"), 186)
  /*  12 - EGENERIC */             ERR(N_("General mishap"), 197)
  /*  13 - EROFS */                ERR(N_("Read-only file system"), 212)
  /*  14 - ECHMEDIA */             ERR(N_("Media changed"), 234)
  /*  15 - ENODEV */               ERR(N_("No such device"), 248)
  /*  16 - EBADSEC */              ERR(N_("Bad sectors found"), 263)
  /*  17 - ENOMEDIUM */            ERR(N_("No medium found"), 281)
  /*  18 - EINSERT */              ERR(N_("Insert media"), 297)
  /*  19 - EDRVNRSP */             ERR(N_("Drive not responding"), 310)
  /*  20 - ESRCH */                ERR(N_("No such process"), 331)
  /*  21 - ECHILD */               ERR(N_("No child process"), 347)
  /*  22 - EDEADLK */              ERR(N_("Resource deadlock avoided"), 364)
  /*  23 - ENOTBLK */              ERR(N_("Block device required"), 390)
  /*  24 - EISDIR */               ERR(N_("Is a directory"), 412)
  /*  25 - EINVAL */               ERR(N_("Invalid argument"), 427)
  /*  26 - EFTYPE */               ERR(N_("Inappropriate file type of format"), 444)
  /*  27 - EILSEQ */               ERR(N_("Illegal byte sequence"), 478)
  /*  28 */                        NONE
  /*  29 */                        NONE
  /*  30 */                        NONE
  /*  31 */                        NONE
  /*  32 - ENOSYS */               ERR(N_("Function not implemented"), 500)
  /*  33 - ENOENT */               ERR(N_("No such file or directory"), 525)
  /*  34 - ENOTDIR */              ERR(N_("Not a directory"), 551)
  /*  35 - EMFILE */               ERR(N_("Too many open files"), 567)
  /*  36 - EACCES */               ERR(N_("Permission denied"), 587)
  /*  37 - EBADF */                ERR(N_("Bad file descriptor"), 605)
  /*  38 - EPERM */                ERR(N_("Operation not permitted"), 625)
  /*  39 - ENOMEM */               ERR(N_("Cannot allocate memory"), 649)
  /*  40 - EFAULT */               ERR(N_("Bad address"), 672)
  /*  41 */                        NONE
  /*  42 */                        NONE
  /*  43 */                        NONE
  /*  44 */                        NONE
  /*  45 */                        NONE
  /*  46 - ENXIO */                ERR(N_("No such device or address"), 684)
  /*  47 */                        NONE
  /*  48 - EXDEV */                ERR(N_("Cross-device link"), 710)
  /*  49 - ENMFILES */             ERR(N_("No more matching filenames"), 728)
  /*  50 - ENFILE */               ERR(N_("File table overflow"), 755)
  /*  51 */                        NONE
  /*  52 */                        NONE
  /*  53 */                        NONE
  /*  54 */                        NONE
  /*  55 */                        NONE
  /*  56 */                        NONE
  /*  57 */                        NONE
  /*  58 - ELOCKED */              ERR(N_("Locking conflict"), 775)
  /*  59 - ENSLOCK */              ERR(N_("No such lock"), 792)
  /*  60 */                        NONE
  /*  61 */                        NONE
  /*  62 */                        NONE
  /*  63 */                        NONE
  /*  64 - EBADARG */              ERR(N_("Bad argument"), 805)
  /*  65 - EINTERNAL */            ERR(N_("Internal error"), 818)
  /*  66 - ENOEXEC */              ERR(N_("Invalid executable file format"), 833)
  /*  67 - ESBLOCK */              ERR(N_("Memory block growth failure"), 864)
  /*  68 - EBREAK */               ERR(N_("Aborted by user"), 892)
  /*  69 - EXCPT */                ERR(N_("Terminated with bombs"), 908)
  /*  70 - ETXTBSY */              ERR(N_("Text file busy"), 930)
  /*  71 - EFBIG */                ERR(N_("File too big"), 945)
  /*  72 */                        NONE
  /*  73 */                        NONE
  /*  74 */                        NONE
  /*  75 */                        NONE
  /*  76 */                        NONE
  /*  77 */                        NONE
  /*  78 */                        NONE
  /*  79 */                        NONE
  /*  80 - ELOOP */                ERR(N_("Too many symbolic links"), 958)
  /*  81 - EPIPE */                ERR(N_("Broken pipe"), 982)
  /*  82 - EMLINK */               ERR(N_("Too many links"), 994)
  /*  83 - ENOTEMPTY */            ERR(N_("Directory not empty"), 1009)
  /*  84 */                        NONE
  /*  85 - EEXIST */               ERR(N_("File exists"), 1029)
  /*  86 - ENAMETOOLONG */         ERR(N_("Name too long"), 1041)
  /*  87 - ENOTTY */               ERR(N_("Not a tty"), 1055)
  /*  88 - ERANGE */               ERR(N_("Range error"), 1065)
  /*  89 - EDOM */                 ERR(N_("Domain error"), 1077)
  /*  90 - EIO */                  ERR(N_("I/O error"), 1090)
  /*  91 - ENOSPC */               ERR(N_("No space on device"), 1100)
  /*  92 */                        NONE
  /*  93 */                        NONE
  /*  94 */                        NONE
  /*  95 */                        NONE
  /*  96 */                        NONE
  /*  97 */                        NONE
  /*  98 */                        NONE
  /*  99 */                        NONE
  /* 100 - EPROCLIM */             ERR(N_("Too many processes"), 1119)
  /* 101 - EUSERS */               ERR(N_("Too many users"), 1138)
  /* 102 - EDQUOT */               ERR(N_("Quota exceeded"), 1153)
  /* 103 - ESTALE */               ERR(N_("Stale NFS file handle"), 1168)
  /* 104 - EREMOTE */              ERR(N_("Object is remote"), 1190)
  /* 105 - EBADRPC */              ERR(N_("RPC struct is bad"), 1207)
  /* 106 - ERPCMISMATCH */         ERR(N_("RPC version wrong"), 1225)
  /* 107 - EPROGUNAVAIL */         ERR(N_("RPC program not available"), 1243)
  /* 108 - EPROGMISMATCH */        ERR(N_("RPC program version wrong"), 1269)
  /* 109 - EPROCUNAVAIL */         ERR(N_("RPC bad procedure for program"), 1295)
  /* 110 - ENOLCK */               ERR(N_("No locks available"), 1325)
  /* 111 - EAUTH */                ERR(N_("Authentication error"), 1344)
  /* 112 - ENEEDAUTH */            ERR(N_("Need authenticator"), 1365)
  /* 113 - EBACKGROUND */          ERR(N_("Inappropriate operation for background process"), 1384)
  /* 114 - EBADMSG */              ERR(N_("Not a data message"), 1431)
  /* 115 - EIDRM */                ERR(N_("Identifier removed"), 1450)
  /* 116 - EMULTIHOP */            ERR(N_("Multihop attempted"), 1469)
  /* 117 - ENODATA */              ERR(N_("No data available"), 1488)
  /* 118 - ENOLINK */              ERR(N_("Link has been severed"), 1506)
  /* 119 - ENOMSG */               ERR(N_("No message of desired type"), 1528)
  /* 120 - ENOSR */                ERR(N_("Out of streams resources"), 1555)
  /* 121 - ENOSTR */               ERR(N_("Device not a stream"), 1580)
  /* 122 - EOVERFLOW */            ERR(N_("Value too large for defined data type"), 1600)
  /* 123 - EPROTO */               ERR(N_("Protocol error"), 1638)
  /* 124 - ETIME */                ERR(N_("Timer expired"), 1653)
  /* 125 - E2BIG */                ERR(N_("Argument list too long"), 1667)
  /* 126 - ERESTART */             ERR(N_("Interrupted system call restarted"), 1690)
  /* 127 - ECHRNG */               ERR(N_("Channel number out of range"), 1724)
  /* 128 - EINTR */                ERR(N_("Interrupted function call"), 1752)
  /* 129 - ESNDLOCKED */           ERR(N_("Sound system is already locked"), 1778)
  /* 130 - ESNDNOTLOCK */          ERR(N_("Sound system is not locked"), 1809)
  /* 131 - EL2NSYNC */             ERR(N_("Level 2 not synchronized"), 1836)
  /* 132 - EL3HLT */               ERR(N_("Level 3 halted"), 1861)
  /* 133 - EL3RST */               ERR(N_("Level 3 reset"), 1876)
  /* 134 - ELNRNG */               ERR(N_("Link number out of range"), 1890)
  /* 135 - EUNATCH */              ERR(N_("Protocol driver not attached"), 1915)
  /* 136 - ENOCSI */               ERR(N_("No CSI structure available"), 1944)
  /* 137 - EL2HLT */               ERR(N_("Level 2 halted"), 1971)
  /* 138 - EBADE */                ERR(N_("Invalid exchange"), 1986)
  /* 139 - EXFULL */               ERR(N_("Exchange full"), 2003)
  /* 140 - ENOANO */               ERR(N_("No anode"), 2017)
  /* 141 - EBADRQC */              ERR(N_("Invalid request code"), 2026)
  /* 142 - EBADSLT */              ERR(N_("Invalid slot"), 2047)
  /* 143 - EBFONT */               ERR(N_("Bad font file format"), 2060)
  /* 144 - ENONET */               ERR(N_("Machine is not on the network"), 2081)
  /* 145 - ENOPKG */               ERR(N_("Package is not installed"), 2111)
  /* 146 - EADV */                 ERR(N_("Advertise error"), 2136)
  /* 147 - ESRMNT */               ERR(N_("Srmount error"), 2152)
  /* 148 - ECOMM */                ERR(N_("Communication error on send"), 2166)
  /* 149 - EDOTDOT */              ERR(N_("RFS specific error"), 2194)
  /* 150 - ELIBACC */              ERR(N_("Cannot access a needed shared library"), 2213)
  /* 151 - ELIBBAD */              ERR(N_("Accessing a corrupted shared library"), 2251)
  /* 152 - ELIBSCN */              ERR(N_(".lib section in a.out corrupted"), 2288)
  /* 153 - ELIBMAX */              ERR(N_("Attempting to link in too many shared libraries"), 2320)
  /* 154 - ELIBEXEC */             ERR(N_("Cannot exec a shared library directly"), 2368)
  /* 155 - ESTRPIPE */             ERR(N_("Streams pipe error"), 2406)
  /* 156 - EUCLEAN */              ERR(N_("Structure needs cleaning"), 2425)
  /* 157 - ENOTNAM */              ERR(N_("Not a XENIX named type file"), 2450)
  /* 158 - ENAVAIL */              ERR(N_("No XENIX semaphores available"), 2478)
  /* 159 - EREMOTEIO */            ERR(N_("Remote I/O error"), 2508)
  /* 160 */                        NONE
  /* 161 */                        NONE
  /* 162 */                        NONE
  /* 163 */                        NONE
  /* 164 */                        NONE
  /* 165 */                        NONE
  /* 166 */                        NONE
  /* 167 */                        NONE
  /* 168 */                        NONE
  /* 169 */                        NONE
  /* 170 */                        NONE
  /* 171 */                        NONE
  /* 172 */                        NONE
  /* 173 */                        NONE
  /* 174 */                        NONE
  /* 175 */                        NONE
  /* 176 */                        NONE
  /* 177 */                        NONE
  /* 178 */                        NONE
  /* 179 */                        NONE
  /* 180 */                        NONE
  /* 181 */                        NONE
  /* 182 */                        NONE
  /* 183 */                        NONE
  /* 184 */                        NONE
  /* 185 */                        NONE
  /* 186 */                        NONE
  /* 187 */                        NONE
  /* 188 */                        NONE
  /* 189 */                        NONE
  /* 190 */                        NONE
  /* 191 */                        NONE
  /* 192 */                        NONE
  /* 193 */                        NONE
  /* 194 */                        NONE
  /* 195 */                        NONE
  /* 196 */                        NONE
  /* 197 */                        NONE
  /* 198 */                        NONE
  /* 199 */                        NONE
  /* 200 */                        NONE
  /* 201 */                        NONE
  /* 202 */                        NONE
  /* 203 */                        NONE
  /* 204 */                        NONE
  /* 205 */                        NONE
  /* 206 */                        NONE
  /* 207 */                        NONE
  /* 208 */                        NONE
  /* 209 */                        NONE
  /* 210 */                        NONE
  /* 211 */                        NONE
  /* 212 */                        NONE
  /* 213 */                        NONE
  /* 214 */                        NONE
  /* 215 */                        NONE
  /* 216 */                        NONE
  /* 217 */                        NONE
  /* 218 */                        NONE
  /* 219 */                        NONE
  /* 220 */                        NONE
  /* 221 */                        NONE
  /* 222 */                        NONE
  /* 223 */                        NONE
  /* 224 */                        NONE
  /* 225 */                        NONE
  /* 226 */                        NONE
  /* 227 */                        NONE
  /* 228 */                        NONE
  /* 229 */                        NONE
  /* 230 */                        NONE
  /* 231 */                        NONE
  /* 232 */                        NONE
  /* 233 */                        NONE
  /* 234 */                        NONE
  /* 235 */                        NONE
  /* 236 */                        NONE
  /* 237 */                        NONE
  /* 238 */                        NONE
  /* 239 */                        NONE
  /* 240 */                        NONE
  /* 241 */                        NONE
  /* 242 */                        NONE
  /* 243 */                        NONE
  /* 244 */                        NONE
  /* 245 */                        NONE
  /* 246 */                        NONE
  /* 247 */                        NONE
  /* 248 */                        NONE
  /* 249 */                        NONE
  /* 250 */                        NONE
  /* 251 */                        NONE
  /* 252 */                        NONE
  /* 253 */                        NONE
  /* 254 */                        NONE
  /* 255 */                        NONE
  /* 256 */                        NONE
  /* 257 */                        NONE
  /* 258 */                        NONE
  /* 259 */                        NONE
  /* 260 */                        NONE
  /* 261 */                        NONE
  /* 262 */                        NONE
  /* 263 */                        NONE
  /* 264 */                        NONE
  /* 265 */                        NONE
  /* 266 */                        NONE
  /* 267 */                        NONE
  /* 268 */                        NONE
  /* 269 */                        NONE
  /* 270 */                        NONE
  /* 271 */                        NONE
  /* 272 */                        NONE
  /* 273 */                        NONE
  /* 274 */                        NONE
  /* 275 */                        NONE
  /* 276 */                        NONE
  /* 277 */                        NONE
  /* 278 */                        NONE
  /* 279 */                        NONE
  /* 280 */                        NONE
  /* 281 */                        NONE
  /* 282 */                        NONE
  /* 283 */                        NONE
  /* 284 */                        NONE
  /* 285 */                        NONE
  /* 286 */                        NONE
  /* 287 */                        NONE
  /* 288 */                        NONE
  /* 289 */                        NONE
  /* 290 */                        NONE
  /* 291 */                        NONE
  /* 292 */                        NONE
  /* 293 */                        NONE
  /* 294 */                        NONE
  /* 295 */                        NONE
  /* 296 */                        NONE
  /* 297 */                        NONE
  /* 298 */                        NONE
  /* 299 */                        NONE
  /* 300 - ENOTSOCK */             ERR(N_("Socket operation on non-socket"), 2525)
  /* 301 - EDESTADDRREQ */         ERR(N_("Destination address required"), 2556)
  /* 302 - EMSGSIZE */             ERR(N_("Message too long"), 2585)
  /* 303 - EPROTOTYPE */           ERR(N_("Protocol wrong type for socket"), 2602)
  /* 304 - ENOPROTOOPT */          ERR(N_("Protocol not available"), 2633)
  /* 305 - EPROTONOSUPPORT */      ERR(N_("Protocol not supported"), 2656)
  /* 306 - ESOCKTNOSUPPORT */      ERR(N_("Socket type not supported"), 2679)
  /* 307 - EOPNOTSUPP */           ERR(N_("Operation not supported"), 2705)
  /* 308 - EPFNOSUPPORT */         ERR(N_("Protocol family not supported"), 2729)
  /* 309 - EAFNOSUPPORT */         ERR(N_("Address family not supported by protocol"), 2759)
  /* 310 - EADDRINUSE */           ERR(N_("Address already in use"), 2800)
  /* 311 - EADDRNOTAVAIL */        ERR(N_("Cannot assign requested address"), 2823)
  /* 312 - ENETDOWN */             ERR(N_("Network is down"), 2855)
  /* 313 - ENETUNREACH */          ERR(N_("Network is unreachable"), 2871)
  /* 314 - ENETRESET */            ERR(N_("Network dropped connection on reset"), 2894)
  /* 315 - ECONNABORTED */         ERR(N_("Software caused connection abort"), 2930)
  /* 316 - ECONNRESET */           ERR(N_("Connection reset by peer"), 2963)
  /* 317 - EISCONN */              ERR(N_("Socket is already connected"), 2988)
  /* 318 - ENOTCONN */             ERR(N_("Socket is not connected"), 3016)
  /* 319 - ESHUTDOWN */            ERR(N_("Cannot send after shutdown"), 3040)
  /* 320 - ETIMEDOUT */            ERR(N_("Connection timed out"), 3067)
  /* 321 - ECONNREFUSED */         ERR(N_("Connection refused"), 3088)
  /* 322 - EHOSTDOWN */            ERR(N_("Host is down"), 3107)
  /* 323 - EHOSTUNREACH */         ERR(N_("No route to host"), 3120)
  /* 324 - EALREADY */             ERR(N_("Operation already in progress"), 3137)
  /* 325 - EINPROGRESS */          ERR(N_("Operation now in progress"), 3167)
  /* 326 - EAGAIN */               ERR(N_("Operation would block"), 3193)
  /* 327 - ENOBUFS */              ERR(N_("No buffer space available"), 3215)
  /* 328 - ETOOMANYREFS */         ERR(N_("Too many references"), 3241)
  /* 329 */                        NONE
  /* 330 */                        NONE
  /* 331 */                        NONE
  /* 332 */                        NONE
  /* 333 */                        NONE
  /* 334 */                        NONE
  /* 335 */                        NONE
  /* 336 */                        NONE
  /* 337 */                        NONE
  /* 338 */                        NONE
  /* 339 */                        NONE
  /* 340 */                        NONE
  /* 341 */                        NONE
  /* 342 */                        NONE
  /* 343 */                        NONE
  /* 344 */                        NONE
  /* 345 */                        NONE
  /* 346 */                        NONE
  /* 347 */                        NONE
  /* 348 */                        NONE
  /* 349 */                        NONE
  /* 350 - ENOTSUP */              ERR(N_("Function not implemented"), 3261)
  /* 351 - ECANCELED */            ERR(N_("Operation canceled"), 3286)
  /* 352 - EOWNERDEAD */           ERR(N_("Owner died"), 3305)
  /* 353 - ENOTRECOVERABLE */      ERR(N_("State not recoverable"), 3316)

#undef ERR
#undef NONE
