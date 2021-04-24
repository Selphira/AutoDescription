STO_type = 0x8
STO_name = 0xc
STO_flags = 0x10
STO_sell_price_markup = 0x14
STO_buy_price_markup = 0x18
STO_depreciation_rate = 0x1c
STO_chance_of_steal_failure = 0x20
STO_capacity = 0x22
STO_items_purchased_offset = 0x2c
STO_items_purchased_count = 0x30
STO_items_for_sale_offset = 0x34
STO_items_for_sale_count = 0x38
STO_lore = 0x3c
STO_id_price = 0x40
STO_rumours_tavern = 0x44
STO_drinks_offset = 0x4c
STO_drinks_count = 0x50
STO_rumours_temple = 0x54
STO_room_flags = 0x5c
STO_price_of_a_peasant_room = 0x60
STO_price_of_a_merchant_room = 0x64
STO_price_of_a_noble_room = 0x68
STO_price_of_a_royal_room = 0x6c
STO_cures_offset = 0x70
STO_cures_count = 0x74


TEXT_SPRINT BGFORGE_STO_DIR ~%BGFORGE_STRUCTURES_DIR%/sto~
PATCH_INCLUDE
  ~%BGFORGE_STO_DIR%/flag.tpp~
  ~%BGFORGE_STO_DIR%/items_sale.tpp~
