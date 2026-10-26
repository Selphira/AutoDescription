
# New engine: cases not supported

| Resource | Problem | Location | Effect data | Reason | Consequence |
|---|---|---|---|---|---|
| BDSW2H01.ITM | spell BDDRAGBL.SPL has no name | equipped effect 3 (opcode 232) > BDDRAGBL.SPL: ability 0, effect 6 | opcode **206**, target **3**, parameter1 **0**, parameter2 **0**, timing **0**, duration **120**, resource **BDDRAGBL** | `opcode206:no_name` | effect ignored |
| HAMM09.ITM | item MINHP1.ITM has no name | ability 0, effect 1, CFTROLL.EFF (opcode 177) | opcode **123**, target **2**, parameter1 **0**, parameter2 **0**, timing **1**, duration **0**, resource **MINHP1** | `opcode123:no_name` | effect ignored |
| OHBREW04.ITM | value 100 of IDS file 6 has no name | ability 0, effect 0, OHBREW04.EFF (opcode 177) | opcode **146**, target **1**, parameter1 **10**, parameter2 **1**, timing **0**, duration **3**, power **10**, resource **OHBREW04** | `versus:ids_name` | not described |
| OHNWAND1.ITM | spell OHNWAND1.SPL has no name | ability 0, effect 0 (opcode 146) > OHNWAND1.SPL: ability 0, effect 6 | opcode **206**, target **2**, parameter1 **0**, parameter2 **0**, timing **0**, duration **24**, resistance **1**, saving throw type **1**, saving throw bonus **-4**, resource **OHNWAND1** | `opcode206:no_name` | effect ignored |
| POTN45.ITM | proficiency 131 has no name | ability 0, effect 39 | opcode **233**, target **1**, parameter1 **1**, parameter2 **131**, timing **0**, duration **600**, power **4**, resistance **1** | `opcode233:no_name` | effect ignored |
| SW2HD1.ITM | spell OHDSW1.SPL has no name | equipped effect 0 (opcode 232) > OHDSW2.SPL: ability 0, effect 0 | opcode **206**, target **1**, parameter1 **-1**, parameter2 **0**, timing **1**, duration **0**, resource **OHDSW1** | `opcode206:no_name` | effect ignored |
| SW2HD1.ITM | spell OHDSW2.SPL has no name | equipped effect 0 (opcode 232) > OHDSW2.SPL: ability 0, effect 1 | opcode **206**, target **1**, parameter1 **-1**, parameter2 **0**, timing **1**, duration **0**, resource **OHDSW2** | `opcode206:no_name` | effect ignored |
