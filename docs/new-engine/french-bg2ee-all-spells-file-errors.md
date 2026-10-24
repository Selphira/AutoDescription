
# New engine: errors in the game files

| Resource | Problem | Location | Effect data | Reason | Consequence |
|---|---|---|---|---|---|
| OHBPR608.SPL | empty resource field | ability 0, effect 0 | opcode **111**, target **1**, parameter1 **0**, parameter2 **2**, timing **1**, duration **0**, power **6**, resistance **2** | `opcode111:invalid` | not described |
| SPIN530.SPL | invalid mode or no change (mode 0, value 0) | ability 0, effect 0 | opcode **173**, target **2**, parameter1 **0**, parameter2 **0**, timing **0**, duration **36**, resistance **2**, saving throw type **1**, saving throw bonus **-6** | `opcode173:invalid` | not described |
