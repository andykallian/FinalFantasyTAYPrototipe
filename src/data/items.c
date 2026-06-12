#include "items.h"


const ItemDef item_table[ITEM_COUNT] = {
                      /* ==================== MENU ITEMS ==================== */

    /* ITEM_POTION         */
    { "Potion", 30, ITEM_CAT_CONSUMABLE, ITEM_FX_HEAL_HP, 100, 0 },

    /* ITEM_HI_POTION      */
    { "Hi-Potion", 150, ITEM_CAT_CONSUMABLE, ITEM_FX_HEAL_HP, 500, 0 },

    /* ITEM_X_POTION       */
    { "X-Potion", 3000, ITEM_CAT_CONSUMABLE, ITEM_FX_HEAL_HP, 2000, 0 },

    /* ITEM_ETHER          */
    { "Ether", 10000, ITEM_CAT_CONSUMABLE, ITEM_FX_HEAL_MP, 50, 0 },

    /* ITEM_DRY_ETHER      */
    { "Dry Ether", 50000, ITEM_CAT_CONSUMABLE, ITEM_FX_HEAL_MP, 150, 0 },

    /* ITEM_ELIXIR         */
    { "Elixir", 100000, ITEM_CAT_CONSUMABLE, ITEM_FX_HEAL_FULL, 0, 0 },

    /* ITEM_MEGALIXIR      */
    { "Megalixir", 0xFFFF, ITEM_CAT_CONSUMABLE, ITEM_FX_PARTY_FULL, 0, 0 },

    /* ITEM_PHOENIX_DOWN   */
    { "Phoenix Down", 100, ITEM_CAT_CONSUMABLE, ITEM_FX_REVIVE, 0, 0 },

    /* ITEM_GOLD_NEEDLE    */
    { "Gold Needle", 400, ITEM_CAT_CONSUMABLE, ITEM_FX_CURE_STATUS, 0, STATUS_PETRIFY },

    /* ITEM_MAIDENS_KISS   */
    { "Maiden's Kiss", 60, ITEM_CAT_CONSUMABLE, ITEM_FX_CURE_STATUS, 0, STATUS_TOAD },

    /* ITEM_MALLET         */
    { "Mallet", 80, ITEM_CAT_CONSUMABLE, ITEM_FX_CURE_STATUS, 0, STATUS_MINI },

    /* ITEM_DIET_RATION    */
    { "Diet Ration", 100, ITEM_CAT_CONSUMABLE, ITEM_FX_CURE_STATUS, 0, STATUS_PIG },

    /* ITEM_CROSS          */
    { "Cross", 100, ITEM_CAT_CONSUMABLE, ITEM_FX_CURE_STATUS, 0, STATUS_CURSE },

    /* ITEM_ECHO_HERBS     */
    { "Echo Herbs", 50, ITEM_CAT_CONSUMABLE, ITEM_FX_CURE_STATUS, 0, STATUS_SILENCE },

    /* ITEM_EYE_DROPS      */
    { "Eye Drops", 30, ITEM_CAT_CONSUMABLE, ITEM_FX_CURE_STATUS, 0, STATUS_BLIND },

    /* ITEM_ANTIDOTE       */
    { "Antidote", 40, ITEM_CAT_CONSUMABLE, ITEM_FX_CURE_STATUS, 0, STATUS_POISON },

    /* ITEM_REMEDY         */
    { "Remedy", 5000, ITEM_CAT_CONSUMABLE, ITEM_FX_CURE_ALL, 0, 0 },

    /* ITEM_SMALL_TALE     */
    { "Small Tale", 0xFFFF, ITEM_CAT_CONSUMABLE, ITEM_FX_HEAL_HP, 100, 0 },

    /* ITEM_DISCOVERY_BOOK */
    { "Discovery Book", 0xFFFF, ITEM_CAT_STAT, ITEM_FX_RAISE_MAX_MP, 50, 0 },

    /* ITEM_GOLDEN_APPLE   */
    { "Golden Apple", 0xFFFF, ITEM_CAT_STAT, ITEM_FX_RAISE_MAX_HP, 100, 0 },

    /* ITEM_SILVER_APPLE   */
    { "Silver Apple", 0xFFFF, ITEM_CAT_STAT, ITEM_FX_RAISE_MAX_HP, 50, 0 },

    /* ITEM_SOMA_DROP      */
    { "Soma Drop", 0xFFFF, ITEM_CAT_STAT, ITEM_FX_RAISE_MAX_MP, 10, 0 },

    /* ITEM_TENT           */
    { "Tent", 100, ITEM_CAT_CONSUMABLE, ITEM_FX_PARTY_HP, 0, 0 },

    /* ITEM_COTTAGE        */
    { "Cottage", 500, ITEM_CAT_CONSUMABLE, ITEM_FX_PARTY_FULL, 0, 0 },

    /* ITEM_GNOMISH_BREAD  */
    { "Gnomish Bread", 100, ITEM_CAT_CONSUMABLE, ITEM_FX_SIGHT, 0, 0 },

    /* ITEM_EMERGENCY_EXIT */
    { "Emergency Exit", 180, ITEM_CAT_CONSUMABLE, ITEM_FX_EXIT, 0, 0 },

    /* ITEM_GOBLIN         */
    { "Goblin", 0xFFFF, ITEM_CAT_SUMMON, ITEM_FX_TEACH_SUMMON, 0, 0 },

    /* ITEM_BOMB           */
    { "Bomb", 0xFFFF, ITEM_CAT_SUMMON, ITEM_FX_TEACH_SUMMON, 1, 0 },

    /* ITEM_COCKATRICE     */
    { "Cockatrice", 0xFFFF, ITEM_CAT_SUMMON, ITEM_FX_TEACH_SUMMON, 2, 0 },

    /* ITEM_MINDFLAYER     */
    { "Mindflayer", 0xFFFF, ITEM_CAT_SUMMON, ITEM_FX_TEACH_SUMMON, 3, 0 },

    /* ITEM_CHOCOBO        */
    { "Chocobo", 0xFFFF, ITEM_CAT_SUMMON, ITEM_FX_TEACH_SUMMON, 4, 0 },



                      /* ==================== BATTLE ITEMS ==================== */

    /* ITEM_BOMB_FRAGMENT  */
    { "Bomb Fragment", 200, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 0, 0 },

    /* ITEM_BOMB_CRANK     */
    { "Bomb Crank", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 1, 0 },

    /* ITEM_ANTARCTIC_WIND */
    { "Antarctic Wind", 200, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 2, 0 },

    /* ITEM_ARCTIC_WIND    */
    { "Arctic Wind", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 3, 0 },

    /* ITEM_ZEUS_WRATH     */
    { "Zeus's Wrath", 200, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 4, 0 },

    /* ITEM_HEAVENLY_WRATH */
    { "Heavenly Wrath", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 5, 0 },

    /* ITEM_STARDUST       */
    { "Stardust", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 6, 0 },

    /* ITEM_LILITHS_KISS   */
    { "Lilith's Kiss", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 7, 0 },

    /* ITEM_VAMPIRE_FANG   */
    { "Vampire Fang", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 8, 0 },

    /* ITEM_BACCHUS_WINE   */
    { "Bacchus's Wine", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_INFLICT_STATUS, 0, STATUS_BERSERK },

    /* ITEM_HERMES_SANDALS */
    { "Hermes Sandals", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_BUFF_STATUS, 0, STATUS_HASTE },

    /* ITEM_BRONZE_HOURGLASS */
    { "Bronze Hourglass", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_INFLICT_STATUS, 0, STATUS_STOP },

    /* ITEM_SILVER_HOURGLASS */
    { "Silver Hourglass", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_INFLICT_STATUS, 0, STATUS_STOP },

    /* ITEM_GOLD_HOURGLASS */
    { "Gold Hourglass", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_INFLICT_STATUS, 0, STATUS_STOP },

    /* ITEM_SPIDERS_SILK   */
    { "Spider's Silk", 100, ITEM_CAT_BATTLE, ITEM_FX_INFLICT_STATUS, 0, STATUS_SLOW },

    /* ITEM_DECOY          */
    { "Decoy", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_BUFF_STATUS, 0, STATUS_BLINK },

    /* ITEM_RED_FANG       */
    { "Red Fang", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 16, 0 },

    /* ITEM_WHITE_FANG     */
    { "White Fang", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 17, 0 },

    /* ITEM_BLUE_FANG      */
    { "Blue Fang", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 18, 0 },

    /* ITEM_LIGHT_CURTAIN  */
    { "Light Curtain", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_BUFF_STATUS, 0, STATUS_REFLECT },

    /* ITEM_BOMB_CORE      */
    { "Bomb Core", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 20, 0 },

    /* ITEM_LUNAR_CURTAIN  */
    { "Lunar Curtain", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_BUFF_STATUS, 0, STATUS_REFLECT | STATUS_BARRIER },

    /* ITEM_SILENT_BELL    */
    { "Silent Bell", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_INFLICT_STATUS, 0, STATUS_SILENCE },

    /* ITEM_GAIA_DRUM      */
    { "Gaia Drum", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CAST_SPELL, 22, 0 },

    /* ITEM_COEURL_WHISKER */
    { "Coeurl Whisker", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_INSTANT_KO, 0, 0 },

    /* ITEM_BESTIARY       */
    { "Bestiary", 50, ITEM_CAT_BATTLE, ITEM_FX_VIEW_ENEMY, 0, 0 },

    /* ITEM_ALARM_CLOCK    */
    { "Alarm Clock", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CURE_STATUS, 0, STATUS_SLEEP },

    /* ITEM_UNICORN_HORN   */
    { "Unicorn Horn", 0xFFFF, ITEM_CAT_BATTLE, ITEM_FX_CURE_STATUS, 0,
      STATUS_SLEEP | STATUS_HOLD | STATUS_BERSERK | STATUS_CONFUSE },


                      /* ==================== KEY ITEMS ==================== */

    /* ITEM_ADAMANTITE     */
    { "Adamantite", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_ADAMANTINE_PIG */
    { "Adamantine Pig", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_AGARTITE       */
    { "Agartite", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_BARDS_LYRE     */
    { "Bard's Lyre", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_BARON_KEY      */
    { "Baron Key", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_BLACK_TAIL     */
    { "Black Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_BLUE_TAIL      */
    { "Blue Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_BOUQUET        */
    { "Bouquet", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_BRONZE_TAIL    */
    { "Bronze Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_CRYSTAL        */
    { "Crystal", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_DAMCYAN_FLOWERS */
    { "Damcyan Flowers", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_DARK_CRYSTAL   */
    { "Dark Crystal", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_EBONY_TAIL     */
    { "Ebony Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_FRYING_PAN     */
    { "Frying Pan", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_GIL_BIRD_EGG   */
    { "Gil Bird Egg", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_GOLD_TAIL      */
    { "Gold Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_GREEN_TAIL     */
    { "Green Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_GREY_TAIL      */
    { "Grey Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_KOKKOL_ORE     */
    { "Kokkol Ore", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_LADLE          */
    { "Ladle", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_LUSTFUL_LALIHO */
    { "Lustful Lali-ho", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_MEMBERS_CARD   */
    { "Member's Card", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_MEMBERS_WRIT   */
    { "Member's Writ", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_MYTHRIL_BOLT   */
    { "Mythril Bolt", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_MYTHRIL_NUT    */
    { "Mythril Nut", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_MYTHRIL_SPRING */
    { "Mythril Spring", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_PINK_TAIL      */
    { "Pink Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_POETS_NOTEBOOK */
    { "Poet's Notebook", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_PROOF_OF_COURAGE */
    { "Proof of Courage", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_PURPLE_TAIL    */
    { "Purple Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_RAINBOW_TAIL   */
    { "Rainbow Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_RED_TAIL       */
    { "Red Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_SAND_PEARL     */
    { "Sand Pearl", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_SILVER_TAIL    */
    { "Silver Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_SMALL_TAIL     */
    { "Small Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_VIP_CARD       */
    { "VIP Card", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_WHISPERWEED_SEED */
    { "Whisperweed Seed", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

    /* ITEM_WHITE_TAIL     */
    { "White Tail", 0xFFFF, ITEM_CAT_KEY, ITEM_FX_NONE, 0, 0 },

};

const u16 item_count = ITEM_COUNT;
