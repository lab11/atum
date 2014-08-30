#ifndef __APP_H__
#define __APP_H__

#include <stdint.h>

#define ADDR_ALL_ROUTERS "ff02::2"

#define RECEIVER_ADDR "2001:470:1f10:1320::2"
#define RECEIVER_PORT 4001
#define PROFILE_ID "G9T58vZ7Bi"

// Prefix for this node, just set it blank as we have no idea what the prefix
// will be.
#define IN6_PREFIX "::"

#define DATA_TYPE 0
#define VERSION 1

typedef struct {
  char     profile[10]; // GATD profile ID
  uint8_t  type;
  uint8_t  version;
  int16_t  airflow;
  uint32_t seq_no;
} __attribute__((packed)) pkt_data_t;

#endif


// 5): 0x3841c82b2200ffffae99f34f43e598c07c7010200104701f1013200000000000000002f051c70fa1df093761694f504a61705846017f2b
// 03877 got packet (78): 0x4f41c8932200ffff997d0f04004b120041600000000015110f0000000000000000c298e5434ff399ae200104701f101320000000000000000251c70fa10015df093761694f504a61705846017f2b
// 03878 got packet (78): 0x4f41c8942200ffff997d0f04004b120041600000000015110f0000000000000000c298e5434ff39e2d200104701f101320000000000000000251c70fa1001523cc3761694f504a61705846013de2
// 03879 got packet (55): 0x3841c84b2200ffffcb59f34f43e598c07c7010200104701f1013200000000000000002f051c70fa1ff383761694f504a6170584601334b
// 03880 got packet (78): 0x4f41c8952200ffff997d0f04004b120041600000000015110f0000000000000000c298e5434ff359cb200104701f101320000000000000000251c70fa10015ff383761694f504a6170584601334b
// 03881 got packet (55): 0x3841c8e92200ffff2057f34f43e598c07c7010200104701f1013200000000000000002f051c70fa163f43761694f504a617058460122e9
// 03882 got packet (55): 0x3841c8972200ffff4695f34f43e598c07c7010200104701f1013200000000000000002f051c70fa177d63761694f504a61705846011a97
// 03883 got packet (55): 0x3841c8a92200ffff225bf34f43e598c07c7010200104701f1013200000000000000002f051c70fa19f5e3761694f504a6170584601b6a9
// 03885 got packet (55): 0x3841c8192200ffff2cf5df4d49e598c07c7010200104701f1013200000000000000002f051c70fa194233761694f504a6170584604f519
// 03886 got packet (78): 0x4f41c8982200ffff997d0f04004b120041600000000015110f0000000000000000c298e5494ddff52c200104701f101320000000000000000251c70fa1001594233761694f504a6170584604f519
// 03887 got packet (55): 0x3841c8372200ffffc06af34f43e598c07c7010200104701f1013200000000000000002f051c70fa101e43761694f504a61705846019337
// 03888 got packet (78): 0x4f41c8992200ffff997d0f04004b120041600000000015110f0000000000000000c298e5434ff36ac0200104701f101320000000000000000251c70fa1001501e43761694f504a61705846019337
// 03889 got packet (55): 0x3841c8aa2200ffff9158f34f43e598c07c7010200104701f1013200000000000000002f051c70fa1a0c23761694f504a6170584601e3aa
// 03890 got packet (78): 0x4f41c89a2200ffff997d0f04004b120041600000000015110f0000000000000000c298e5434ff35891200104701f101320000000000000000251c70fa10015a0c23761694f504a6170584601e3aa
// 03891 got packet (55): 0x3841c8fb2200ffff38d0df4d49e598c07c7010200104701f1013200000000000000002f051c70fa1d7d63761694f504a617058460435fb
// 03893 got packet (55): 0x3841c868
//                           2200ffffbd66f34f43e598c0
//                           7c7010
//                           200104701f1013200000000000000002
//                           f0
//                           51c7
//                           0fa1
//                           d533
//                           3761694f504a61705846
//                           01
//                           46
//                           68
// 03895 got packet (60): 0x3d41c89d
//                           2200ffff997d0f04004b1200
//                           7ef000
//                           200104701f1013200000000000000002
//                           f0
//                           0bb9
//                           0fa1
//                           3e93
//                           4739543538765a374269
//                           00
//                           01
//                           0f68
//                           00000081
// 03896 got packet (55): 0x3841c8602200ffff86abf34f43e598c07c7010200104701f1013200000000000000002f051c70fa198163761694f504a61705846019a60
// 03897 got packet (55): 0x3841c86b2200ffff0936f34f43e598c07c7010200104701f1013200000000000000002f051c70fa102e93761694f504a6170584601456b
// 03898 got packet (78): 0x4f41c89f2200ffff997d0f04004b120041600000000015110f0000000000000000c298e5434ff33609200104701f101320000000000000000251c70fa1001502e93761694f504a6170584601456b
