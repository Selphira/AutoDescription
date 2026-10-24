
# New engine: cases not supported

| Resource | Problem | Location | Effect data | Reason | Consequence |
|---|---|---|---|---|---|
| BALSHLD.SPL | proficiency 125 has no name | ability 0, effect 2 | opcode **233**, target **1**, parameter1 **1**, parameter2 **125**, timing **9**, duration **0**, resistance **3**, resource **BALSHLD2** | `opcode233:no_name` | effect ignored |
| BALTH07.SPL | no sentence 22060101 for this form (target or probable effect) | ability 0, effect 10 | opcode **206**, target **2**, parameter1 **0**, parameter2 **0**, timing **0**, duration **240**, power **4**, resistance **1**, resource **SPWI412** | `phrase22060100:form1` | not described |
| BHAAL1A.SPL | 22 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| BHAAL1B.SPL | 11 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| BHAAL2A.SPL | opcodes not supported yet: 132 |  |  | `missing_opcodes:132` | not described |
| BHAAL2B.SPL | 8 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| BHAAL3B.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| CDHLYSY2.SPL | spell CDHLYSYM.SPL has no name | ability 0, effect 1 | opcode **206**, target **2**, parameter1 **0**, parameter2 **0**, timing **9**, duration **0**, power **100**, resource **CDHLYSYM** | `opcode206:no_name` | effect ignored |
| CDPR417.SPL | opcodes not supported yet: 224 |  |  | `missing_opcodes:224` | not described |
| CDSTAF12.SPL | 6 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| CDWI917A.SPL | gender set to a given value | ability 0, effect 0, CDWI917A.EFF (opcode 177) | opcode **71**, target **4**, parameter1 **6**, parameter2 **1**, timing **9**, duration **0**, resource **BOTSMITH** | `opcode71:gender_set` | not described |
| DGARCHON.SPL | same effect twice (the old engine merges them) | ability 0, effect 7 | opcode **233**, target **1**, parameter1 **1**, parameter2 **123**, timing **0**, duration **360**, power **7**, resistance **2** | `opcode233:same_effect_twice` | not described |
| DGFAITH.SPL | proficiency 110 has no name | ability 0, effect 13 | opcode **233**, target **1**, parameter1 **1**, parameter2 **110**, timing **0**, duration **138**, power **1**, resistance **3** | `opcode233:no_name` | effect ignored |
| DGRIGHT.SPL | opcodes not supported yet: 250 |  |  | `missing_opcodes:250` | not described |
| JWGLOBE.SPL | 9 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| MARW201.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| MARW301.SPL | opcodes not supported yet: 190 |  |  | `missing_opcodes:190` | not described |
| MARW401.SPL | opcodes not supported yet: 188 |  |  | `missing_opcodes:188` | not described |
| MELIS02.SPL | proficiency 121 has no name | ability 0, effect 1 | opcode **233**, target **1**, parameter1 **2**, parameter2 **121**, timing **0**, duration **62**, power **7**, resistance **3** | `opcode233:no_name` | effect ignored |
| OHBDEMI3.SPL | opcodes not supported yet: 213 |  |  | `missing_opcodes:213` | not described |
| OHBRESTO.SPL | opcodes not supported yet: 224 242 |  |  | `missing_opcodes:224 242` | not described |
| OHBWI212.SPL | 18 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| OHBWI302.SPL | opcodes not supported yet: 136 |  |  | `missing_opcodes:136` | not described |
| OHBWI304.SPL | opcodes not supported yet: 136 |  |  | `missing_opcodes:136` | not described |
| OHBWI308.SPL | 6 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| OHBWI405.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| OHDCUT02.SPL | opcodes not supported yet: 231 |  |  | `missing_opcodes:231` | not described |
| OHHDRAIN.SPL | opcodes not supported yet: 165 |  |  | `missing_opcodes:165` | not described |
| OHHSUMM.SPL | 30 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| OHNDDOOR.SPL | opcodes not supported yet: 124 |  |  | `missing_opcodes:124` | not described |
| OHNRDTEL.SPL | opcodes not supported yet: 68 |  |  | `missing_opcodes:68` | not described |
| OHPRGD10.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| OHTMPS1.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| OHTMPS2.SPL | 5 abilities and no casting level (level rendering not supported yet) | ability 0, effect 0 (opcode 146) > OHTMPS2D.SPL | opcode **146**, target **1**, parameter1 **0**, parameter2 **1**, timing **1**, duration **0**, resource **OHTMPS2D** | `recursion:headers` | not described |
| OHTYR1.SPL | opcodes not supported yet: 242 |  |  | `missing_opcodes:242` | not described |
| OHTYR2.SPL | 6 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL102.SPL | 34 abilities and no casting level (level rendering not supported yet) | ability 0, effect 2 (opcode 146) > SPDN01A.SPL | opcode **146**, target **2**, parameter1 **0**, parameter2 **1**, timing **1**, duration **0**, power **1**, resistance **3**, resource **SPDN01A** | `recursion:headers` | not described |
| SPCL103.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL106.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL121.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL144.SPL | opcodes not supported yet: 250 |  |  | `missing_opcodes:250` | not described |
| SPCL152.SPL | delayed effect casting a spell (the old engine writes it as a condition) | ability 0, effect 77 | opcode **146**, target **1**, parameter1 **1**, parameter2 **1**, timing **4**, duration **30**, resistance **2**, resource **BDDRAGB2** | `recursion:delayed` | not described |
| SPCL211.SPL | 34 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL212.SPL | opcodes not supported yet: 115 | ability 0, effect 1 (opcode 146) > CDDETEVL.SPL | opcode **146**, target **2**, parameter1 **1**, parameter2 **1**, timing **1**, duration **0**, power **1**, resistance **1**, resource **CDDETEVL** | `recursion:missing_opcodes:115` | not described |
| SPCL213.SPL | proficiency 117 has no name | ability 0, effect 2 | opcode **233**, target **2**, parameter1 **1**, parameter2 **117**, timing **0**, duration **60**, power **1**, resistance **3** | `opcode233:no_name` | effect ignored |
| SPCL231.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL232.SPL | opcodes not supported yet: 220 |  |  | `missing_opcodes:220` | not described |
| SPCL233.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL236.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL237.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL238.SPL | 8 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL239.SPL | spell SPCL239A.SPL has no name | ability 0, effect 1 | opcode **206**, target **1**, parameter1 **-1**, parameter2 **0**, timing **0**, duration **5**, resource **SPCL239A** | `opcode206:no_name` | effect ignored |
| SPCL239.SPL | spell already described by this resource | ability 0, effect 2 | opcode **146**, target **2**, parameter1 **0**, parameter2 **1**, timing **1**, duration **0**, resistance **1**, resource **SPCL239A** | `recursion:repeated` | not described |
| SPCL321.SPL | immunities of the ability with different fields | ability 0, effect 3 | opcode **101**, target **1**, parameter1 **0**, parameter2 **210**, timing **0**, duration **60**, resistance **2**, resource **SPCL321** | `opcode101:ability_group_fields` | not described |
| SPCL342.SPL | opcodes not supported yet: 192 |  |  | `missing_opcodes:192` | not described |
| SPCL412.SPL | opcodes not supported yet: 252 |  |  | `missing_opcodes:252` | not described |
| SPCL414.SPL | opcodes not supported yet: 252 |  |  | `missing_opcodes:252` | not described |
| SPCL423.SPL | 4 abilities and no casting level (level rendering not supported yet) | ability 0, effect 1 (opcode 248) > BDPWEAPN.EFF (opcode 146) > BDPWEAPN.SPL | opcode **146**, target **2**, parameter1 **0**, parameter2 **1**, timing **1**, duration **0**, resource **BDPWEAPN** | `recursion:headers` | not described |
| SPCL521.SPL | opcodes not supported yet: 250 |  |  | `missing_opcodes:250` | not described |
| SPCL522.SPL | 10 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL621.SPL | opcodes not supported yet: 214 |  |  | `missing_opcodes:214` | not described |
| SPCL622.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL623.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL624.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL625.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL721.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL722.SPL | 10 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL731.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL732.SPL | opcodes not supported yet: 220 |  |  | `missing_opcodes:220` | not described |
| SPCL741.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL742.SPL | opcodes not supported yet: 185 |  |  | `missing_opcodes:185` | not described |
| SPCL815.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL902.SPL | EFF file with a level restriction | ability 0, effect 0 (opcode 248) > SPCL902.EFF | opcode **248**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **12**, resistance **2**, resource **SPCL902** | `recursion:eff_level` | not described |
| SPCL903.SPL | EFF file with a level restriction | ability 0, effect 0 (opcode 248) > SPCL903.EFF | opcode **248**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **12**, resistance **2**, resource **SPCL903** | `recursion:eff_level` | not described |
| SPCL907.SPL | 15 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL910.SPL | opcodes not supported yet: 252 |  |  | `missing_opcodes:252` | not described |
| SPCL911.SPL | opcodes not supported yet: 252 |  |  | `missing_opcodes:252` | not described |
| SPCL912.SPL | opcodes not supported yet: 252 |  |  | `missing_opcodes:252` | not described |
| SPCL915.SPL | opcodes not supported yet: 302 |  |  | `missing_opcodes:302` | not described |
| SPCL916.SPL | opcodes not supported yet: 303 |  |  | `missing_opcodes:303` | not described |
| SPCL920.SPL | opcodes not supported yet: 251 |  |  | `missing_opcodes:251` | not described |
| SPCL923.SPL | 8 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL928.SPL | opcode 42 is only described as an equipped effect | ability 0, effect 1 | opcode **42**, target **1**, parameter1 **1**, parameter2 **32**, timing **9**, duration **0**, resistance **2** | `opcode42:ability` | not described |
| SPCL929.SPL | opcode 42 is only described as an equipped effect | ability 0, effect 1 | opcode **42**, target **1**, parameter1 **1**, parameter2 **64**, timing **9**, duration **0**, resistance **2** | `opcode42:ability` | not described |
| SPCL930.SPL | opcode 42 is only described as an equipped effect | ability 0, effect 1 | opcode **42**, target **1**, parameter1 **1**, parameter2 **128**, timing **9**, duration **0**, resistance **2** | `opcode42:ability` | not described |
| SPCL935.SPL | 8 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPCL936.SPL | opcodes not supported yet: 236 |  |  | `missing_opcodes:236` | not described |
| SPCL937.SPL | opcodes not supported yet: 213 |  |  | `missing_opcodes:213` | not described |
| SPCL941.SPL | opcodes not supported yet: 208 |  |  | `missing_opcodes:208` | not described |
| SPDD03.SPL | opcodes not supported yet: 165 |  |  | `missing_opcodes:165` | not described |
| SPDM102.SPL | 18 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPDM106.SPL | 18 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPDM108.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPDR101.SPL | 9 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPDR301.SPL | 6 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPDR401.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPDR501.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPDR601.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN103.SPL | opcodes not supported yet: 132 |  |  | `missing_opcodes:132` | not described |
| SPIN104.SPL | condition 43 not supported | ability 0, effect 0 | opcode **318**, target **2**, parameter1 **0**, parameter2 **43**, timing **0**, duration **0**, power **1**, resource **SPIN104** | `opcode318:stat` | not described |
| SPIN106.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN109.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN113.SPL | 18 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN117.SPL | immunities of the ability with different fields | ability 0, effect 0 | opcode **101**, target **1**, parameter1 **0**, parameter2 **210**, timing **0**, duration **120** | `opcode101:ability_group_fields` | not described |
| SPIN120.SPL | opcodes not supported yet: 115 | ability 0, effect 1 (opcode 146) > CDDETEVL.SPL | opcode **146**, target **2**, parameter1 **1**, parameter2 **1**, timing **1**, duration **0**, power **1**, resistance **1**, resource **CDDETEVL** | `recursion:missing_opcodes:115` | not described |
| SPIN121.SPL | same effect twice (the old engine merges them) | ability 0, effect 20 | opcode **233**, target **2**, parameter1 **1**, parameter2 **117**, timing **0**, duration **60**, power **1**, resistance **1** | `opcode233:same_effect_twice` | not described |
| SPIN122.SPL | polymorph back to natural form | ability 0, effect 17 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3600000**, resistance **2** | `opcode135:natural_form` | not described |
| SPIN123.SPL | polymorph back to natural form | ability 0, effect 17 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3600000**, resistance **2** | `opcode135:natural_form` | not described |
| SPIN124.SPL | polymorph back to natural form | ability 0, effect 17 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3600000**, resistance **2** | `opcode135:natural_form` | not described |
| SPIN150.SPL | polymorph back to natural form | ability 0, effect 17 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3600000** | `opcode135:natural_form` | not described |
| SPIN151.SPL | polymorph back to natural form | ability 0, effect 17 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3600000** | `opcode135:natural_form` | not described |
| SPIN529.SPL | polymorph back to natural form | ability 0, effect 19 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3666000**, resistance **3** | `opcode135:natural_form` | not described |
| SPIN538.SPL | effect from an EFF file | ability 0, effect 4, PLYSQUWE.EFF (opcode 177) | opcode **111**, target **2**, parameter1 **1**, parameter2 **1**, timing **0**, duration **3600000**, power **4**, resistance **1**, saving throw type **16**, saving throw bonus **-4**, resource **SQUIRP** | `opcode111:external` | not described |
| SPIN542.SPL | opcodes not supported yet: 238 |  |  | `missing_opcodes:238` | not described |
| SPIN544.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN545.SPL | condition 43 not supported | ability 0, effect 0 | opcode **318**, target **2**, parameter1 **0**, parameter2 **43**, timing **0**, duration **0**, power **4**, resistance **2**, resource **SPIN545** | `opcode318:stat` | not described |
| SPIN572.SPL | no text for form 1 (1 target, 2 probable, 3 probable on the target) | ability 0, effect 1 | opcode **93**, target **2**, parameter1 **4**, parameter2 **0**, timing **4**, duration **48**, power **3**, resistance **2** | `opcode93:form1` | not described |
| SPIN580.SPL | opcodes not supported yet: 211 |  |  | `missing_opcodes:211` | not described |
| SPIN608.SPL | no sentence 22060101 for this form (target or probable effect) | ability 0, effect 7 | opcode **206**, target **2**, parameter1 **0**, parameter2 **0**, timing **0**, duration **7200**, power **10**, resistance **3**, resource **SPWI611** | `phrase22060100:form1` | not described |
| SPIN613.SPL | opcodes not supported yet: 283 |  |  | `missing_opcodes:283` | not described |
| SPIN623.SPL | effect from an EFF file | ability 0, effect 4, PLYRABWE.EFF (opcode 177) | opcode **111**, target **2**, parameter1 **1**, parameter2 **1**, timing **0**, duration **120**, power **4**, resource **SQUIRP** | `opcode111:external` | not described |
| SPIN633.SPL | opcodes not supported yet: 193 |  |  | `missing_opcodes:193` | not described |
| SPIN634.SPL | opcodes not supported yet: 283 |  |  | `missing_opcodes:283` | not described |
| SPIN635.SPL | opcodes not supported yet: 283 |  |  | `missing_opcodes:283` | not described |
| SPIN648.SPL | hold of a creature type | ability 0, effect 3 | opcode **175**, target **2**, parameter1 **1**, parameter2 **3**, timing **1**, duration **0**, power **1**, resistance **2** | `opcode175:creature_type` | not described |
| SPIN651.SPL | opcodes not supported yet: 193 |  |  | `missing_opcodes:193` | not described |
| SPIN655.SPL | no sentence 30100101 for this form (target or probable effect) | ability 0, effect 6 | opcode **206**, target **2**, parameter1 **0**, parameter2 **0**, timing **0**, duration **90**, power **6**, resistance **1**, resource **SPWI305** | `phrase30100100:form1` | not described |
| SPIN667.SPL | polymorph back to natural form | ability 0, effect 19 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3666000**, resistance **3** | `opcode135:natural_form` | not described |
| SPIN676.SPL | no text for form 1 (1 target, 2 probable, 3 probable on the target) | ability 0, effect 23 | opcode **284**, target **2**, parameter1 **1**, parameter2 **0**, timing **0**, duration **300**, power **1**, resistance **3** | `opcode284:form1` | not described |
| SPIN684.SPL | opcodes not supported yet: 220 |  |  | `missing_opcodes:220` | not described |
| SPIN685.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN686.SPL | proficiency 128 has no name | ability 0, effect 9 | opcode **233**, target **1**, parameter1 **4**, parameter2 **128**, timing **0**, duration **24**, power **6**, resistance **3** | `opcode233:no_name` | effect ignored |
| SPIN687.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN694.SPL | 8 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN695.SPL | opcodes not supported yet: 273 |  |  | `missing_opcodes:273` | not described |
| SPIN696.SPL | opcodes not supported yet: 115 150 220 |  |  | `missing_opcodes:115 150 220` | not described |
| SPIN697.SPL | 2 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN698.SPL | 2 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN704.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN710.SPL | proficiency 116 has no name | ability 0, effect 14 | opcode **233**, target **1**, parameter1 **2**, parameter2 **116**, timing **0**, duration **324**, power **6**, resistance **2** | `opcode233:no_name` | effect ignored |
| SPIN714.SPL | 6 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN718.SPL | polymorph back to natural form | ability 0, effect 19 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3666000**, resistance **3** | `opcode135:natural_form` | not described |
| SPIN718A.SPL | polymorph back to natural form | ability 0, effect 19 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3666000**, resistance **3** | `opcode135:natural_form` | not described |
| SPIN736.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN737.SPL | opcodes not supported yet: 261 |  |  | `missing_opcodes:261` | not described |
| SPIN774.SPL | opcodes not supported yet: 213 |  |  | `missing_opcodes:213` | not described |
| SPIN788.SPL | opcodes not supported yet: 211 |  |  | `missing_opcodes:211` | not described |
| SPIN826.SPL | 3 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN827.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN828.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPIN837.SPL | opcodes not supported yet: 231 |  |  | `missing_opcodes:231` | not described |
| SPIN852.SPL | opcodes not supported yet: 247 |  |  | `missing_opcodes:247` | not described |
| SPIN853.SPL | opcodes not supported yet: 185 |  |  | `missing_opcodes:185` | not described |
| SPIN891.SPL | effect with a creature type grouped with other effects | ability 0, effect 24, MOOND8.EFF (opcode 177) | opcode **12**, target **2**, parameter1 **5**, parameter2 **4194304**, timing **4**, duration **12**, saving throw type **16777216**, saving throw bonus **0**, parameter3 **4** | `opcode177:versus_group` | not described |
| SPIN944.SPL | opcodes not supported yet: 210 |  |  | `missing_opcodes:210` | not described |
| SPIN956.SPL | 10 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPINHUM.SPL | polymorph back to natural form | ability 0, effect 17 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3600000**, resistance **2** | `opcode135:natural_form` | not described |
| SPJA01.SPL | opcodes not supported yet: 367 | ability 0, effect 1 (opcode 326) > SPJA01A.SPL | opcode **326**, target **2**, parameter1 **3**, parameter2 **103**, timing **1**, duration **0**, power **5**, resistance **2**, resource **SPJA01A** | `recursion:missing_opcodes:367` | not described |
| SPMDSLAY.SPL | item SLAYERWP.ITM has no name | ability 0, effect 4 | opcode **112**, target **1**, parameter1 **0**, parameter2 **0**, timing **1**, duration **0**, resistance **2**, resource **SLAYERWP** | `opcode112:no_name` | not described |
| SPPR104.SPL | opcodes not supported yet: 115 | ability 0, effect 1 (opcode 146) > CDDETEVL.SPL | opcode **146**, target **2**, parameter1 **1**, parameter2 **1**, timing **1**, duration **0**, power **1**, resistance **1**, resource **CDDETEVL** | `recursion:missing_opcodes:115` | not described |
| SPPR107.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR109.SPL | opcodes not supported yet: 153 |  |  | `missing_opcodes:153` | not described |
| SPPR110.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR111.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR150.SPL | opcodes not supported yet: 346 |  |  | `missing_opcodes:346` | not described |
| SPPR201.SPL | opcodes not supported yet: 129 |  |  | `missing_opcodes:129` | not described |
| SPPR202.SPL | 18 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR203.SPL | opcodes not supported yet: 131 | ability 0, effect 0 (opcode 146) > SPPR203D.SPL | opcode **146**, target **1**, parameter1 **0**, parameter2 **1**, timing **1**, duration **0**, resource **SPPR203D** | `recursion:missing_opcodes:131` | not described |
| SPPR205.SPL | opcodes not supported yet: 150 |  |  | `missing_opcodes:150` | not described |
| SPPR205D.SPL | opcodes not supported yet: 150 |  |  | `missing_opcodes:150` | not described |
| SPPR206.SPL | 11 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR208.SPL | hold of a creature type | ability 0, effect 3 | opcode **175**, target **2**, parameter1 **1**, parameter2 **3**, timing **0**, duration **60**, power **2**, resistance **1**, saving throw type **1**, saving throw bonus **0** | `opcode175:creature_type` | not described |
| SPPR209.SPL | opcodes not supported yet: 115 |  |  | `missing_opcodes:115` | not described |
| SPPR210.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR211.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR213.SPL | 18 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR214.SPL | opcodes not supported yet: 132 |  |  | `missing_opcodes:132` | not described |
| SPPR250.SPL | no sentence 22060101 for this form (target or probable effect) | ability 0, effect 9 | opcode **206**, target **2**, parameter1 **0**, parameter2 **0**, timing **0**, duration **5**, power **2**, resource **SPPR250** | `phrase22060100:form1` | not described |
| SPPR301.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR302.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR304.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR305.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR306.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR307.SPL | opcodes not supported yet: 26 |  |  | `missing_opcodes:26` | not described |
| SPPR312.SPL | no text for form 1 (1 target, 2 probable, 3 probable on the target) | ability 0, effect 1 | opcode **97**, target **2**, parameter1 **75**, parameter2 **1**, timing **0**, duration **60**, power **3**, resistance **3** | `opcode97:form1` | not described |
| SPPR313.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR314.SPL | 15 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR318.SPL | opcodes not supported yet: 273 |  |  | `missing_opcodes:273` | not described |
| SPPR319.SPL | same effect twice (the old engine merges them) | ability 0, effect 6 | opcode **233**, target **2**, parameter1 **1**, parameter2 **120**, timing **0**, duration **42**, power **3**, resistance **1**, saving throw type **2**, saving throw bonus **-4** | `opcode233:same_effect_twice` | not described |
| SPPR350.SPL | opcodes not supported yet: 242 337 |  |  | `missing_opcodes:242 337` | not described |
| SPPR402.SPL | effect of an EFF file that the old engine keeps in another form: header block not supported | ability 0, effect 0 | opcode **177**, target **1**, parameter1 **0**, parameter2 **2**, timing **0**, duration **180**, resistance **2**, resource **SPANIM1** | `spell_header:opcode177_eff_fields` | not described |
| SPPR403.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR406.SPL | proficiency 133 has no name | ability 0, effect 7 | opcode **233**, target **2**, parameter1 **1**, parameter2 **133**, timing **0**, duration **36**, power **4**, resistance **3** | `opcode233:no_name` | effect ignored |
| SPPR407.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR408.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR409.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR411.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR412.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR415.SPL | opcodes not supported yet: 239 |  |  | `missing_opcodes:239` | not described |
| SPPR417.SPL | opcodes not supported yet: 224 |  |  | `missing_opcodes:224` | not described |
| SPPR450.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR501.SPL | effect of an EFF file that the old engine keeps in another form: header block not supported | ability 0, effect 0 | opcode **177**, target **1**, parameter1 **0**, parameter2 **2**, timing **0**, duration **180**, resistance **3**, resource **SPANIM2** | `spell_header:opcode177_eff_fields` | not described |
| SPPR503.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR505.SPL | opcodes not supported yet: 220 |  |  | `missing_opcodes:220` | not described |
| SPPR506.SPL | 8 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR507.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR508.SPL | 10 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR509.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR512.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR513.SPL | opcodes not supported yet: 250 |  |  | `missing_opcodes:250` | not described |
| SPPR514.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR515.SPL | effect of an EFF file that the old engine keeps in another form: header block not supported | ability 0, effect 7 | opcode **177**, target **1**, parameter1 **0**, parameter2 **2**, timing **0**, duration **66**, power **5**, resistance **1**, resource **SPPR515D** | `spell_header:opcode177_eff_fields` | not described |
| SPPR515D.SPL | condition 43 not supported | ability 0, effect 0 | opcode **318**, target **2**, parameter1 **0**, parameter2 **43**, timing **0**, duration **0**, power **5**, resource **SPPR515D** | `opcode318:stat` | not described |
| SPPR517.SPL | same effect twice (the old engine merges them) | ability 0, effect 5 | opcode **233**, target **2**, parameter1 **2**, parameter2 **120**, timing **0**, duration **36**, power **5**, resistance **1** | `opcode233:same_effect_twice` | not described |
| SPPR601.SPL | 10 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR602.SPL | effect of an EFF file that the old engine keeps in another form: header block not supported | ability 0, effect 0 | opcode **177**, target **1**, parameter1 **0**, parameter2 **2**, timing **0**, duration **240**, resistance **3**, resource **SPANIM3** | `spell_header:opcode177_eff_fields` | not described |
| SPPR603.SPL | effect of an EFF file that the old engine keeps in another form: header block not supported | ability 0, effect 4 | opcode **177**, target **1**, parameter1 **0**, parameter2 **2**, timing **0**, duration **62**, power **6**, resistance **3**, resource **SPPR603D** | `spell_header:opcode177_eff_fields` | not described |
| SPPR604.SPL | effect of an EFF file that the old engine keeps in another form: header block not supported | ability 0, effect 0 | opcode **177**, target **1**, parameter1 **0**, parameter2 **2**, timing **0**, duration **240**, resistance **3**, resource **SPANIM4** | `spell_header:opcode177_eff_fields` | not described |
| SPPR605.SPL | 10 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR609.SPL | condition 43 not supported | ability 0, effect 0 | opcode **318**, target **2**, parameter1 **0**, parameter2 **43**, timing **0**, duration **0**, power **6**, resistance **2**, resource **SPPR609** | `opcode318:stat` | not described |
| SPPR611.SPL | opcodes not supported yet: 261 |  |  | `missing_opcodes:261` | not described |
| SPPR612.SPL | identical effects with different exceptions | ability 0, effect 23, BOLTDEM.EFF (opcode 177) | opcode **12**, target **2**, parameter1 **0**, parameter2 **4194304**, timing **1**, duration **0**, dice **10d6** | `opcode324:exceptions_identical` | not described |
| SPPR613.SPL | same effect twice (the old engine merges them) | ability 0, effect 31 | opcode **233**, target **1**, parameter1 **1**, parameter2 **122**, timing **0**, duration **54**, power **6**, resistance **3** | `opcode233:same_effect_twice` | not described |
| SPPR650.SPL | 10 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR698.SPL | effect of an EFF file that the old engine keeps in another form: header block not supported | ability 0, effect 4 | opcode **177**, target **1**, parameter1 **0**, parameter2 **2**, timing **0**, duration **62**, power **6**, resistance **1**, resource **SPPR698D** | `spell_header:opcode177_eff_fields` | not described |
| SPPR701.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR702.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR705.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR706.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR707.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR708.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR709.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR710.SPL | level restriction of an effect from an EFF file not supported | ability 0, effect 1, DEATH.EFF (opcode 177) | opcode **13**, target **2**, parameter1 **0**, parameter2 **4**, timing **1**, duration **0**, dice **3d0**, parameter3 **2** | `application:level` | not described |
| SPPR711.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR713.SPL | opcodes not supported yet: 224 242 |  |  | `missing_opcodes:224 242` | not described |
| SPPR715.SPL | level restriction of an effect from an EFF file not supported | ability 0, effect 0, DEATH.EFF (opcode 177) | opcode **13**, target **2**, parameter1 **0**, parameter2 **4**, timing **1**, duration **0**, dice **3d0**, parameter3 **2** | `application:level` | not described |
| SPPR717.SPL | repeated effect casting a spell | ability 0, effect 6 | opcode **146**, target **2**, parameter1 **0**, parameter2 **1**, timing **4**, duration **0**, power **7**, resistance **1**, resource **FLPR717A** | `recursion:series` | not described |
| SPPR718.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR719.SPL | opcodes not supported yet: 209 |  |  | `missing_opcodes:209` | not described |
| SPPR721.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR722.SPL | grouped effect with exceptions | ability 0, effect 8 | opcode **12**, target **2**, parameter1 **0**, parameter2 **65536**, timing **4**, duration **12**, power **7**, resistance **1**, dice **1d6**, saving throw type **16777217**, saving throw bonus **0**, special **256** | `opcode318:exceptions_group` | not described |
| SPPR723.SPL | no sentence 30100103 for this form (target or probable effect) | ability 0, effect 9 | opcode **206**, target **3**, parameter1 **74011**, parameter2 **0**, timing **0**, duration **60**, resistance **2**, probability1 **100**, probability2 **70**, resource **SPPR724** | `phrase30100100:form3` | not described |
| SPPR724.SPL | no sentence 30100101 for this form (target or probable effect) | ability 0, effect 3 | opcode **206**, target **3**, parameter1 **74011**, parameter2 **0**, timing **0**, duration **60**, resistance **2**, resource **SPPR723** | `phrase30100100:form1` | not described |
| SPPR725.SPL | effect of an EFF file that the old engine keeps in another form: header block not supported | ability 0, effect 3 | opcode **177**, target **1**, parameter1 **0**, parameter2 **2**, timing **0**, duration **60**, power **7**, resistance **3**, resource **SPPR725D** | `spell_header:opcode177_eff_fields` | not described |
| SPPR726.SPL | 8 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR727.SPL | 8 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR729.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR730.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPPR750.SPL | opcodes not supported yet: 213 |  |  | `missing_opcodes:213` | not described |
| SPRA301.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPRA302.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPRA304.SPL | effect of an EFF file that the old engine keeps in another form: header block not supported | ability 0, effect 0 | opcode **177**, target **1**, parameter1 **0**, parameter2 **2**, timing **0**, duration **180**, resource **SPANIM1** | `spell_header:opcode177_eff_fields` | not described |
| SPRA305.SPL | effect of an EFF file that the old engine keeps in another form: header block not supported | ability 0, effect 0 | opcode **177**, target **1**, parameter1 **0**, parameter2 **2**, timing **0**, duration **180**, resistance **3**, resource **SPANIM2** | `spell_header:opcode177_eff_fields` | not described |
| SPRA306.SPL | effect of an EFF file that the old engine keeps in another form: header block not supported | ability 0, effect 0 | opcode **177**, target **1**, parameter1 **0**, parameter2 **2**, timing **0**, duration **240**, resistance **3**, resource **SPANIM3** | `spell_header:opcode177_eff_fields` | not described |
| SPSD02.SPL | opcodes not supported yet: 231 |  |  | `missing_opcodes:231` | not described |
| SPWI055.SPL | opcodes not supported yet: 238 |  |  | `missing_opcodes:238` | not described |
| SPWI056.SPL | opcodes not supported yet: 238 |  |  | `missing_opcodes:238` | not described |
| SPWI101.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI103.SPL | opcodes not supported yet: 165 |  |  | `missing_opcodes:165` | not described |
| SPWI105.SPL | opcodes not supported yet: 165 |  |  | `missing_opcodes:165` | not described |
| SPWI107.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI110.SPL | no text for form 1 (1 target, 2 probable, 3 probable on the target) | ability 0, effect 0 | opcode **21**, target **3**, parameter1 **0**, parameter2 **2**, timing **2**, duration **0**, power **1**, resistance **3** | `opcode21:form1` | not described |
| SPWI112.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI113.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI115.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI116.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI118.SPL | 9 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI119.SPL | condition 43 not supported | ability 0, effect 0 | opcode **318**, target **2**, parameter1 **0**, parameter2 **43**, timing **0**, duration **0**, power **1**, resource **SPWI119** | `opcode318:stat` | not described |
| SPWI120.SPL | opcodes not supported yet: 159 |  |  | `missing_opcodes:159` | not described |
| SPWI123.SPL | opcodes not supported yet: 192 |  |  | `missing_opcodes:192` | not described |
| SPWI124.SPL | opcodes not supported yet: 214 |  |  | `missing_opcodes:214` | not described |
| SPWI125.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI201.SPL | 18 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI202.SPL | opcodes not supported yet: 115 | ability 0, effect 1 (opcode 146) > CDDETEVL.SPL | opcode **146**, target **2**, parameter1 **1**, parameter2 **1**, timing **1**, duration **0**, power **2**, resistance **1**, resource **CDDETEVL** | `recursion:missing_opcodes:115` | not described |
| SPWI207.SPL | opcodes not supported yet: 125 |  |  | `missing_opcodes:125` | not described |
| SPWI208.SPL | opcodes not supported yet: 115 |  |  | `missing_opcodes:115` | not described |
| SPWI209.SPL | opcodes not supported yet: 133 |  |  | `missing_opcodes:133` | not described |
| SPWI211.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI212.SPL | 18 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI214.SPL | 18 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI217.SPL | opcodes not supported yet: 165 |  |  | `missing_opcodes:165` | not described |
| SPWI220.SPL | opcodes not supported yet: 217 |  |  | `missing_opcodes:217` | not described |
| SPWI221.SPL | 18 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI222.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI298.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI301.SPL | opcodes not supported yet: 117 |  |  | `missing_opcodes:117` | not described |
| SPWI303.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI304.SPL | 6 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI305.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI306.SPL | hold of a creature type | ability 0, effect 3 | opcode **175**, target **2**, parameter1 **1**, parameter2 **3**, timing **0**, duration **60**, power **3**, resistance **1**, saving throw type **1**, saving throw bonus **-1** | `opcode175:creature_type` | not described |
| SPWI308.SPL | 6 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI309.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI313.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI314.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI315.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI318.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI319.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI320.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI322.SPL | opcodes not supported yet: 220 |  |  | `missing_opcodes:220` | not described |
| SPWI324.SPL | opcodes not supported yet: 185 |  |  | `missing_opcodes:185` | not described |
| SPWI325.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI399.SPL | 6 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI401.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI402.SPL | opcodes not supported yet: 124 |  |  | `missing_opcodes:124` | not described |
| SPWI403.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI405.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI406.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI407.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI408.SPL | 8 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI409.SPL | identical diseases | ability 0, effect 3 | opcode **78**, target **2**, parameter1 **2**, parameter2 **5**, timing **1**, duration **0**, power **4**, saving throw type **1**, saving throw bonus **0** | `opcode78:group` | not described |
| SPWI410.SPL | opcodes not supported yet: 26 |  |  | `missing_opcodes:26` | not described |
| SPWI411.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI412.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI413.SPL | opcodes not supported yet: 185 204 | ability 0, effect 2 (opcode 146) > SPWI413A.SPL | opcode **146**, target **2**, parameter1 **0**, parameter2 **1**, timing **1**, duration **0**, power **4**, resistance **1**, saving throw type **1**, saving throw bonus **0**, resource **SPWI413A** | `recursion:missing_opcodes:185 204` | not described |
| SPWI414.SPL | delayed effect casting a spell (the old engine writes it as a condition) | ability 0, effect 8 | opcode **148**, target **2**, parameter1 **1**, parameter2 **1**, timing **4**, duration **600**, power **4**, resistance **3**, resource **SPWI414A** | `recursion:delayed` | not described |
| SPWI416.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI417.SPL | opcodes not supported yet: 345 |  |  | `missing_opcodes:345` | not described |
| SPWI418.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI421.SPL | opcodes not supported yet: 222 |  |  | `missing_opcodes:222` | not described |
| SPWI423.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI424.SPL | opcodes not supported yet: 239 |  |  | `missing_opcodes:239` | not described |
| SPWI425.SPL | 14 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI489.SPL | polymorph back to natural form | ability 0, effect 17 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3600000**, resistance **2** | `opcode135:natural_form` | not described |
| SPWI490.SPL | polymorph back to natural form | ability 0, effect 17 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3600000**, resistance **2** | `opcode135:natural_form` | not described |
| SPWI491.SPL | polymorph back to natural form | ability 0, effect 17 | opcode **135**, target **1**, parameter1 **0**, parameter2 **0**, timing **0**, duration **3600000**, resistance **2** | `opcode135:natural_form` | not described |
| SPWI501.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI503.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI504.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI505.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI507.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI508.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI510.SPL | opcodes not supported yet: 214 |  |  | `missing_opcodes:214` | not described |
| SPWI511.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI512.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI514.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI515.SPL | opcodes not supported yet: 220 |  |  | `missing_opcodes:220` | not described |
| SPWI516.SPL | opcodes not supported yet: 165 |  |  | `missing_opcodes:165` | not described |
| SPWI517.SPL | 12 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI518.SPL | 10 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI519.SPL | opcodes not supported yet: 226 |  |  | `missing_opcodes:226` | not described |
| SPWI520.SPL | opcodes not supported yet: 165 |  |  | `missing_opcodes:165` | not described |
| SPWI521.SPL | opcodes not supported yet: 165 |  |  | `missing_opcodes:165` | not described |
| SPWI522.SPL | 16 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI523.SPL | 7 abilities and no casting level (level rendering not supported yet) | ability 0, effect 0 (opcode 148) > SPWI523D.SPL | opcode **148**, target **1**, parameter1 **0**, parameter2 **1**, timing **1**, duration **0**, resource **SPWI523D** | `recursion:headers` | not described |
| SPWI602.SPL | 9 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI603.SPL | 9 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI606.SPL | 9 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI607.SPL | opcodes not supported yet: 236 |  |  | `missing_opcodes:236` | not described |
| SPWI608.SPL | 9 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI609.SPL | opcodes not supported yet: 220 |  |  | `missing_opcodes:220` | not described |
| SPWI611.SPL | proficiency 128 has no name | ability 0, effect 11 | opcode **233**, target **1**, parameter1 **4**, parameter2 **128**, timing **0**, duration **24**, power **6**, resistance **3** | `opcode233:no_name` | effect ignored |
| SPWI613.SPL | 9 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI615.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI616.SPL | opcodes not supported yet: 238 |  |  | `missing_opcodes:238` | not described |
| SPWI617.SPL | 3 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI618.SPL | 9 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI619.SPL | 9 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI620.SPL | opcodes not supported yet: 165 |  |  | `missing_opcodes:165` | not described |
| SPWI621.SPL | opcodes not supported yet: 165 |  |  | `missing_opcodes:165` | not described |
| SPWI622.SPL | opcodes not supported yet: 165 |  |  | `missing_opcodes:165` | not described |
| SPWI623.SPL | 10 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI624.SPL | 9 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI701.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI702.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI703.SPL | opcodes not supported yet: 236 |  |  | `missing_opcodes:236` | not described |
| SPWI705.SPL | proficiency 132 has no name | ability 0, effect 9 | opcode **233**, target **2**, parameter1 **1**, parameter2 **132**, timing **0**, duration **13**, power **7** | `opcode233:no_name` | effect ignored |
| SPWI708.SPL | proficiency 128 has no name | ability 0, effect 11 | opcode **233**, target **1**, parameter1 **1**, parameter2 **128**, timing **0**, duration **24**, power **7**, resistance **3** | `opcode233:no_name` | effect ignored |
| SPWI711.SPL | opcodes not supported yet: 222 238 |  |  | `missing_opcodes:222 238` | not described |
| SPWI714.SPL | opcodes not supported yet: 238 |  |  | `missing_opcodes:238` | not described |
| SPWI715.SPL | opcodes not supported yet: 210 |  |  | `missing_opcodes:210` | not described |
| SPWI716.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI717.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI718.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI719.SPL | 8 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI720.SPL | opcodes not supported yet: 241 |  |  | `missing_opcodes:241` | not described |
| SPWI721.SPL | 7 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI802.SPL | proficiency 116 has no name | ability 0, effect 11 | opcode **233**, target **1**, parameter1 **2**, parameter2 **116**, timing **0**, duration **288**, power **8**, resistance **1** | `opcode233:no_name` | effect ignored |
| SPWI803.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI804.SPL | opcodes not supported yet: 236 |  |  | `missing_opcodes:236` | not described |
| SPWI805.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI808.SPL | proficiency 128 has no name | ability 0, effect 12 | opcode **233**, target **1**, parameter1 **2**, parameter2 **128**, timing **0**, duration **24**, power **8**, resistance **3** | `opcode233:no_name` | effect ignored |
| SPWI810.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI811.SPL | 3 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI812.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI813.SPL | opcodes not supported yet: 213 |  |  | `missing_opcodes:213` | not described |
| SPWI816.SPL | 3 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI817.SPL | opcodes not supported yet: 209 |  |  | `missing_opcodes:209` | not described |
| SPWI818.SPL | timing 3 not supported in an ability | ability 0, effect 6 | opcode **39**, target **2**, parameter1 **0**, parameter2 **1**, timing **3**, duration **1**, power **8**, resistance **1**, special **13** | `application:timing` | not described |
| SPWI853.SPL | opcodes not supported yet: 185 |  |  | `missing_opcodes:185` | not described |
| SPWI897.SPL | opcodes not supported yet: 209 |  |  | `missing_opcodes:209` | not described |
| SPWI898.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI899.SPL | 5 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI902.SPL | opcodes not supported yet: 259 |  |  | `missing_opcodes:259` | not described |
| SPWI907.SPL | proficiency 128 has no name | ability 0, effect 14 | opcode **233**, target **1**, parameter1 **3**, parameter2 **128**, timing **0**, duration **24**, power **9**, resistance **3** | `opcode233:no_name` | effect ignored |
| SPWI909.SPL | opcodes not supported yet: 231 |  |  | `missing_opcodes:231` | not described |
| SPWI910.SPL | opcodes not supported yet: 211 |  |  | `missing_opcodes:211` | not described |
| SPWI912.SPL | opcodes not supported yet: 209 |  |  | `missing_opcodes:209` | not described |
| SPWI917.SPL | opcodes not supported yet: 212 |  |  | `missing_opcodes:212` | not described |
| SPWI918.SPL | timing 3 not supported in an ability | ability 0, effect 6 | opcode **39**, target **2**, parameter1 **0**, parameter2 **1**, timing **3**, duration **1**, power **9**, resistance **1**, special **13** | `application:timing` | not described |
| SPWI920.SPL | 20 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI921.SPL | opcodes not supported yet: 188 |  |  | `missing_opcodes:188` | not described |
| SPWI923.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI924.SPL | 4 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWI926.SPL | opcodes not supported yet: 124 |  |  | `missing_opcodes:124` | not described |
| SPWI959.SPL | opcodes not supported yet: 210 |  |  | `missing_opcodes:210` | not described |
| SPWI960.SPL | opcodes not supported yet: 209 |  |  | `missing_opcodes:209` | not described |
| SPWI982.SPL | opcodes not supported yet: 68 |  |  | `missing_opcodes:68` | not described |
| SPWI994.SPL | opcodes not supported yet: 124 |  |  | `missing_opcodes:124` | not described |
| SPWI995.SPL | opcodes not supported yet: 68 |  |  | `missing_opcodes:68` | not described |
| SPWISH07.SPL | opcodes not supported yet: 224 242 |  |  | `missing_opcodes:224 242` | not described |
| SPWISH09.SPL | proficiency 121 has no name | ability 0, effect 2 | opcode **233**, target **1**, parameter1 **1**, parameter2 **121**, timing **0**, duration **60**, power **7**, resistance **3** | `opcode233:no_name` | effect ignored |
| SPWISH11.SPL | EFF file with a level restriction | ability 0, effect 0 (opcode 248) > SPCL903.EFF | opcode **248**, target **3**, parameter1 **0**, parameter2 **0**, timing **0**, duration **12**, power **9**, resistance **2**, resource **SPCL903** | `recursion:eff_level` | not described |
| SPWISH12.SPL | 15 abilities: level sections not supported yet |  |  | `spell:abilities` | not described |
| SPWISH17.SPL | opcodes not supported yet: 188 231 |  |  | `missing_opcodes:188 231` | not described |
| SPWISH31.SPL | no sentence 5000131 for this form (target or probable effect) | ability 0, effect 2 | opcode **166**, target **4**, parameter1 **40**, parameter2 **1**, timing **0**, duration **126**, power **9**, resistance **3** | `phrase5000130:form1` | not described |
| SPWISH34.SPL | no text for form 1 (1 target, 2 probable, 3 probable on the target) | ability 0, effect 0 | opcode **22**, target **4**, parameter1 **-5**, parameter2 **0**, timing **0**, duration **60**, power **9**, resistance **3** | `opcode22:form1` | not described |
| SPWISH36.SPL | no sentence 22060101 for this form (target or probable effect) | ability 0, effect 7 | opcode **206**, target **2**, parameter1 **0**, parameter2 **0**, timing **0**, duration **90**, power **9**, resistance **1**, resource **SPCL521** | `phrase22060100:form1` | not described |
| SPWISH37.SPL | no sentence 22060101 for this form (target or probable effect) | ability 0, effect 7 | opcode **206**, target **2**, parameter1 **0**, parameter2 **0**, timing **0**, duration **90**, power **9**, resistance **1**, resource **SPCL521** | `phrase22060100:form1` | not described |
| SPWISH40.SPL | no sentence 22060101 for this form (target or probable effect) | ability 0, effect 7 | opcode **206**, target **2**, parameter1 **0**, parameter2 **0**, timing **0**, duration **90**, power **9**, resistance **1**, resource **SPCL521** | `phrase22060100:form1` | not described |
| SPWISH46.SPL | opcodes not supported yet: 224 242 |  |  | `missing_opcodes:224 242` | not described |
| SPWM101.SPL | effect of an EFF file that the old engine keeps in another form: header block not supported | ability 0, effect 2 | opcode **177**, target **1**, parameter1 **0**, parameter2 **2**, timing **0**, duration **90**, power **5**, resistance **1**, resource **SPWM101D** | `spell_header:opcode177_eff_fields` | not described |
| SPWM101D.SPL | condition 43 not supported | ability 0, effect 0 | opcode **318**, target **2**, parameter1 **0**, parameter2 **43**, timing **0**, duration **0**, power **5**, resource **SPWM101D** | `opcode318:stat` | not described |
| SPWM113.SPL | weapon removed later by opcode 112 | ability 0, effect 12 | opcode **112**, target **2**, parameter1 **0**, parameter2 **0**, timing **4**, duration **70**, power **4**, resource **WSWOLF** | `opcode111:remove_group` | not described |
| SPWM122.SPL | hold of a creature type | ability 0, effect 3 | opcode **175**, target **2**, parameter1 **1**, parameter2 **3**, timing **0**, duration **60**, power **2**, resistance **1**, saving throw type **1**, saving throw bonus **0** | `opcode175:creature_type` | not described |
| SPWM125.SPL | opcodes not supported yet: 117 |  |  | `missing_opcodes:117` | not described |
| SPWM140.SPL | opcodes not supported yet: 243 |  |  | `missing_opcodes:243` | not described |
| SPWM141.SPL | random treasure rndtre05 | ability 0, effect 1 | opcode **122**, target **2**, parameter1 **0**, parameter2 **0**, timing **1**, duration **0**, resource **RNDTRE05** | `opcode122:random_treasure` | not described |
| SPWM142.SPL | no text for form 1 (1 target, 2 probable, 3 probable on the target) | ability 0, effect 1 | opcode **73**, target **2**, parameter1 **2**, parameter2 **0**, timing **0**, duration **60**, power **2**, resistance **1** | `opcode73:form1` | not described |
| SPWM143.SPL | opcodes not supported yet: 222 |  |  | `missing_opcodes:222` | not described |
| SPWM145.SPL | opcodes not supported yet: 190 |  |  | `missing_opcodes:190` | not described |
| SPWM183.SPL | effect from an EFF file | ability 0, effect 8, PLYSQUWE.EFF (opcode 177) | opcode **111**, target **2**, parameter1 **1**, parameter2 **1**, timing **0**, duration **40**, power **4**, resistance **1**, saving throw type **16**, saving throw bonus **0**, resource **SQUIRP** | `opcode111:external` | not described |
| SPWM191.SPL | opcodes not supported yet: 190 |  |  | `missing_opcodes:190` | not described |
| STAF11.SPL | opcodes not supported yet: 259 |  |  | `missing_opcodes:259` | not described |
