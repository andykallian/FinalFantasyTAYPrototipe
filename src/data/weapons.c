#include "weapons.h"

/* spell_id placeholder — substituir pelos defines de spells.h quando implementado
   0=Fire 1=Blizzard 2=Thunder 3=Osmose 4=Pig 5=Heal 6=Cura 7=Poisona 8=Basuna
   9=Confuse 10=Protect 11=Dispel 12=Silence 13=Raise 14=Esuna 15=Haste
   16=Blink 17=Quake 18=Blitz 19=Flood 20=MagicArrow 21=DancingDagger 

WEAPON FORMAT

{
    "Name",         // Nome exibido no jogo

    type,           // Tipo da arma (WTYPE_SWORD, WTYPE_AXE, WTYPE_BOW, etc)

    attack,         // Poder de ataque base da arma
                    // Soma no cálculo de dano físico.

    accuracy,       // Bônus (ou penalidade) de precisão da arma.
                    // Ex.: 50 = +50%, -10 = -10%.

    element,        // Elemento associado ao ataque.
                    // ELEM_NONE
                    // ELEM_FIRE
                    // ELEM_ICE
                    // ELEM_THUNDER
                    // ELEM_WIND
                    // ELEM_WATER
                    // ELEM_HOLY
                    // ELEM_DARK
                    // Pode combinar com |

    flags,          // Propriedades especiais da arma.
                    // WFLAG_THROWABLE
                    // WFLAG_LONG_RANGE
                    // WFLAG_HP_DRAIN
                    // WFLAG_CASTS_SPELL
                    // WFLAG_ANTI_DRAGON
                    // WFLAG_ANTI_GHOST
                    // WFLAG_ANTI_DEMON
                    // WFLAG_ANTI_MECH
                    // WFLAG_ANTI_GIANT
                    // WFLAG_ANTI_MAGE
                    // WFLAG_TWO_HANDED
                    // etc.
                    // Pode combinar com |

    spell_id,       // Magia acionada pela arma.
                    // Usado somente quando WFLAG_CASTS_SPELL está presente.
                    // 0 = nenhuma magia.

    inflict,        // Status infligido on-hit (SINF_* bitmask).
                    // SINF_NONE para armas sem efeito de status.
                    // SINF_SLEEP, SINF_POISON, SINF_PETRIFY, SINF_DEATH, etc.
                    // Pode combinar com |


    equip_mask,     // Máscara de personagens que podem equipar.
                    // EQUIP_CECIL
                    // EQUIP_KAIN
                    // EQUIP_EDGE
                    // EQUIP_SWORD
                    // EQUIP_AXEUSERS
                    // etc.
                    // Pode combinar com |

    buy_price,      // Preço de compra na loja.
                    // 0xFFFF = não pode ser comprada.

    sell_price      // Preço de venda.
                    // 0xFFFF = não pode ser vendida.
}
                    
==============================================================================*/

const WeaponDef weapon_table[WEAPON_COUNT] = {

                      /* ==================== CLAWS ==================== */

  /* WPN_FLAME_CLAWS     */ 
  { "Flame Claws", WTYPE_CLAW, 0, 30, ELEM_FIRE, WFLAG_NONE, 0, SINF_NONE, EQUIP_CLAWUSERS, 350, 175 },
  /* WPN_ICE_CLAWS       */ 
  { "Ice Claws", WTYPE_CLAW, 0, 30, ELEM_ICE, WFLAG_NONE, 0, SINF_NONE, EQUIP_CLAWUSERS, 450, 225 },
  /* WPN_LIGHTNING_CLAWS */ 
  { "Lightning Claws", WTYPE_CLAW, 0, 30, ELEM_THUNDER, WFLAG_ANTI_MECH, 0, SINF_NONE, EQUIP_CLAWUSERS, 550, 275 },
  /* WPN_METAL_KNUCKLES  */ 
  { "Metal Knuckles", WTYPE_CLAW, 0, 30, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_CLAWUSERS, 600, 300 },
  /* WPN_FAERIE_CLAWS    */ 
  { "Faerie Claws", WTYPE_CLAW, 0, 0, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_CLAWUSERS, 0xFFFF, 3000 },
  /* WPN_HELL_CLAWS      */ 
  { "Hell Claws", WTYPE_CLAW, 0, 40, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_CLAWUSERS, 0xFFFF, 3500 },
  /* WPN_CAT_CLAWS       */ 
  { "Cat Claws", WTYPE_CLAW, 0, 40, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_CLAWUSERS, 6500, 3250 },
  /* WPN_GODHAND         */ 
  { "Godhand", WTYPE_CLAW, 0, 40, ELEM_HOLY, WFLAG_NONE, 0, SINF_NONE, EQUIP_CLAWUSERS, 0xFFFF, 20000 },
  /* WPN_DRAGON_CLAWS    */ 
  { "Dragon Claws", WTYPE_CLAW, 0, 50, ELEM_HOLY, WFLAG_ANTI_DRAGON, 0, SINF_NONE, EQUIP_CLAWUSERS, 0xFFFF, 25000 },
  /* WPN_TIGER_FANGS     */ 
  { "Tiger Fangs", WTYPE_CLAW, 0, 50, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_CLAWUSERS, 0xFFFF, 30000 },

                      /* ==================== RODS ==================== */

  /* WPN_ROD             */
  { "Rod", WTYPE_ROD, 3, -10, ELEM_NONE, WFLAG_CASTS_SPELL, 20, SINF_NONE, EQUIP_MAGE, 100, 50 },
  /* WPN_ICE_ROD         */
  { "Ice Rod", WTYPE_ROD, 5, -5, ELEM_ICE, WFLAG_CASTS_SPELL, 1, SINF_NONE, EQUIP_MAGE, 220, 110 },
  /* WPN_FLAME_ROD       */
  { "Flame Rod", WTYPE_ROD, 7, -5, ELEM_FIRE, WFLAG_CASTS_SPELL, 0, SINF_NONE, EQUIP_MAGE, 380, 190 },
  /* WPN_HEALING_ROD     */
  { "Healing Rod", WTYPE_ROD, 9, 0, ELEM_NONE, WFLAG_CASTS_SPELL, 5, SINF_NONE, EQUIP_MAGE, 0xFFFF, 2000 },
  /* WPN_THUNDER_ROD     */
  { "Thunder Rod", WTYPE_ROD, 10, -5, ELEM_THUNDER, WFLAG_CASTS_SPELL, 2, SINF_NONE, EQUIP_MAGE, 700, 350 },
  /* WPN_LILITH_ROD      */
  { "Lilith Rod", WTYPE_ROD, 13, -40, ELEM_NONE, WFLAG_CASTS_SPELL|WFLAG_HP_DRAIN, 3, SINF_POISON, EQUIP_MAGE, 0xFFFF, 3000 },
  /* WPN_POLYMORPH_ROD   */
  { "Polymorph Rod", WTYPE_ROD, 15, 0, ELEM_NONE, WFLAG_CASTS_SPELL, 4, SINF_NONE, EQUIP_MAGE, 1250, 625 },
  /* WPN_WIZARD_ROD      */
  { "Wizard Rod", WTYPE_ROD, 21, 5, ELEM_FIRE|ELEM_ICE|ELEM_THUNDER, WFLAG_CASTS_SPELL, 21, SINF_NONE, EQUIP_MAGE, 5000, 2500 },
  /* WPN_RECOVERY_ROD    */
  { "Recovery Rod", WTYPE_ROD, 25, 5, ELEM_NONE, WFLAG_CASTS_SPELL, 6, SINF_NONE, EQUIP_MAGE, 0xFFFF, 4000 },
  /* WPN_FAERIE_ROD      */
  { "Faerie Rod", WTYPE_ROD, 30, 5, ELEM_NONE, WFLAG_CASTS_SPELL, 9, SINF_NONE, EQUIP_MAGE, 0xFFFF, 6000 },
  /* WPN_STARDUST_ROD    */
  { "Stardust Rod", WTYPE_ROD, 45, 10, ELEM_NONE, WFLAG_CASTS_SPELL, 21, SINF_NONE, EQUIP_MAGE, 0xFFFF, 15000 },


                      /* ==================== STAVES ==================== */

  /* WPN_STAFF           */
  { "Staff", WTYPE_STAFF, 4, -5, ELEM_NONE, WFLAG_CASTS_SPELL, 7, SINF_NONE, EQUIP_STAFFUSERS, 160, 80 },
  /* WPN_HEALING_STAFF   */
  { "Healing Staff", WTYPE_STAFF, 8, 0, ELEM_NONE, WFLAG_CASTS_SPELL, 5, SINF_NONE, EQUIP_STAFFUSERS, 480, 240 },
  /* WPN_MYTHRIL_STAFF   */
  { "Mythril Staff", WTYPE_STAFF, 12, 5, ELEM_NONE, WFLAG_CASTS_SPELL, 8, SINF_NONE, EQUIP_STAFFUSERS, 4000, 2000 },
  /* WPN_PSYCHO_SPIRAL   */
  { "Psycho Spiral", WTYPE_STAFF, 14, 10, ELEM_NONE, WFLAG_CASTS_SPELL, 9, SINF_NONE, EQUIP_STAFFUSERS, 2000, 1000 },
  /* WPN_PROTECT_STAFF   */
  { "Protect Staff", WTYPE_STAFF, 15, 10, ELEM_NONE, WFLAG_CASTS_SPELL, 10, SINF_NONE, EQUIP_STAFFUSERS, 0xFFFF, 3000 },
  /* WPN_POWER_STAFF     */
  { "Power Staff", WTYPE_STAFF, 30, 0, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_STAFFUSERS, 6000, 3000 },
  /* WPN_AURA_STAFF      */
  { "Aura Staff", WTYPE_STAFF, 36, 10, ELEM_NONE, WFLAG_CASTS_SPELL, 11, SINF_NONE, EQUIP_STAFFUSERS, 0xFFFF, 8000 },
  /* WPN_MASTERS_STAFF   */
  { "Master's Staff", WTYPE_STAFF, 42, 15, ELEM_NONE, WFLAG_CASTS_SPELL, 6, SINF_NONE, EQUIP_STAFFUSERS, 10000, 5000 },
  /* WPN_SAGES_STAFF     */
  { "Sage's Staff", WTYPE_STAFF, 45, 15, ELEM_NONE, WFLAG_CASTS_SPELL, 13, SINF_NONE, EQUIP_STAFFUSERS, 0xFFFF, 12000 },
  /* WPN_SERAPHIM_MACE   */
  { "Seraphim Mace", WTYPE_STAFF, 50, 20, ELEM_NONE, WFLAG_CASTS_SPELL, 14, SINF_NONE, EQUIP_STAFFUSERS, 0xFFFF, 15000 },
  /* WPN_RUNE_STAFF      */
  { "Rune Staff", WTYPE_STAFF, 52, 10, ELEM_NONE, WFLAG_CASTS_SPELL, 12, SINF_NONE, EQUIP_STAFFUSERS, 0xFFFF, 18000 },

                      /* ==================== SWORDS ==================== */

  /* WPN_BROADSWORD      */
  { "Broadsword", WTYPE_SWORD, 10, 50, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_SWORD, 200, 100 },
  /* WPN_EBONY_BLADE     */
  { "Ebony Blade", WTYPE_SWORD, 20, 40, ELEM_DARK, WFLAG_NONE, 0, SINF_NONE, EQUIP_GOLBEZ, 0xFFFF, 2000 },
  /* WPN_LONGSWORD       */
  { "Longsword", WTYPE_SWORD, 20, 35, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_SWORD, 450, 225 },
  /* WPN_IRON_SWORD      */
  { "Iron Sword", WTYPE_SWORD, 30, 35, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_SWORD, 1000, 500 },
  /* WPN_ANCIENT_SWORD   */
  { "Ancient Sword", WTYPE_SWORD, 35, 27, ELEM_NONE, WFLAG_NONE, 0, SINF_GRADPETRIFY, EQUIP_SWORD, 0xFFFF, 3500 },
  /* WPN_CORAL_BLADE     */
  { "Coral Blade", WTYPE_SWORD, 38, 35, ELEM_THUNDER, WFLAG_NONE, 0, SINF_NONE, EQUIP_SWORD, 2500, 1250 },
  /* WPN_BLOOD_SWORD     */
  { "Blood Sword", WTYPE_SWORD, 45, 0, ELEM_NONE, WFLAG_HP_DRAIN, 0, SINF_NONE, EQUIP_SWORD, 0xFFFF, 5000 },
  /* WPN_FALCHION        */
  { "Falchion", WTYPE_SWORD, 48, 40, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_KAIN, 0xFFFF, 4000 },
  /* WPN_MYTHRIL_SWORD   */
  { "Mythril Sword", WTYPE_SWORD, 50, 35, ELEM_NONE, WFLAG_ANTI_GHOST, 0, SINF_NONE, EQUIP_SWORD, 6000, 3000 },
  /* WPN_SLEEP_BLADE     */
  { "Sleep Blade", WTYPE_SWORD, 55, 27, ELEM_NONE, WFLAG_CASTS_SPELL, 41, SINF_SLEEP, EQUIP_SWORD, 0xFFFF, 6000 },
  /* WPN_FLAME_SWORD     */
  { "Flame Sword", WTYPE_SWORD, 65, 30, ELEM_FIRE, WFLAG_NONE, 0, SINF_NONE, EQUIP_SWORD, 14000, 7000 },
  /* WPN_ICEBRAND        */
  { "Icebrand", WTYPE_SWORD, 75, 30, ELEM_ICE, WFLAG_NONE, 0, SINF_NONE, EQUIP_SWORD, 26000, 13000 },
  /* WPN_STONEBLADE      */
  { "Stoneblade", WTYPE_SWORD, 77, 16, ELEM_NONE, WFLAG_NONE, 0, SINF_PETRIFY, EQUIP_SWORD, 0xFFFF, 12000 },
  /* WPN_DEMON_SLAYER    */
  { "Demon Slayer", WTYPE_SWORD, 82, 40, ELEM_NONE, WFLAG_ANTI_DEMON, 0, SINF_NONE, EQUIP_SWORD, 40000, 20000 },
  /* WPN_ENHANCEMENT_SWD */
  { "Enhancement Sword", WTYPE_SWORD, 82, 40, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_SWORD, 37000, 18500 },
  /* WPN_DEFENDER        */
  { "Defender", WTYPE_SWORD, 105, 40, ELEM_NONE, WFLAG_CASTS_SPELL, 10, SINF_NONE, EQUIP_SWORD, 57000, 28500 },
  /* WPN_ULTIMA_WEAPON   */
  { "Ultima Weapon", WTYPE_SWORD, 180, 50, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_SWORD, 0xFFFF, 0xFFFF },

                        /* ==================== HOLY SWORDS ==================== */

  /* WPN_EXCALIPOOR      */
  { "Excalipoor", WTYPE_HOLYSWORD, 1, 99, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN, 0xFFFF, 0xFFFF },
  /* WPN_KINGSWORD       */
  { "Kingsword", WTYPE_HOLYSWORD, 40, 40, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_CECIL, 0xFFFF, 5000 },
  /* WPN_LUSTROUS_SWORD  */
  { "Lustrous Sword", WTYPE_HOLYSWORD, 99, 50, ELEM_HOLY, WFLAG_NONE, 0, SINF_NONE, EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN, 0xFFFF, 21000 },
  /* WPN_EXCALIBUR       */
  { "Excalibur", WTYPE_HOLYSWORD, 120, 50, ELEM_HOLY, WFLAG_NONE, 0, SINF_NONE, EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN, 0xFFFF, 0xFFFF },
  /* WPN_RAGNAROK        */
  { "Ragnarok", WTYPE_HOLYSWORD, 150, 50, ELEM_HOLY, WFLAG_NONE, 0, SINF_NONE, EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN, 0xFFFF, 0xFFFF },


                      /* ==================== SPEARS ==================== */

  /* WPN_SPEAR           */
  { "Spear", WTYPE_SPEAR, 9, 50, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_SPEARUSERS, 60, 30 },
  /* WPN_JAVELIN         */
  { "Javelin", WTYPE_SPEAR, 22, 50, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_SPEARUSERS, 650, 325 },
  /* WPN_TRIDENT         */
  { "Trident", WTYPE_SPEAR, 31, 35, ELEM_THUNDER, WFLAG_NONE, 0, SINF_NONE, EQUIP_SPEARUSERS, 0xFFFF, 4000 },
  /* WPN_PARTISAN        */
  { "Partisan", WTYPE_SPEAR, 42, 30, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_SPEARUSERS, 0xFFFF, 6000 },
  /* WPN_WIND_SPEAR      */
  { "Wind Spear", WTYPE_SPEAR, 55, 30, ELEM_WIND, WFLAG_NONE, 0, SINF_NONE, EQUIP_SPEARUSERS, 0xFFFF, 9000 },
  /* WPN_FLAME_LANCE     */
  { "Flame Lance", WTYPE_SPEAR, 66, 30, ELEM_FIRE, WFLAG_CASTS_SPELL, 0, SINF_NONE, EQUIP_SPEARUSERS, 0xFFFF, 12000 },
  /* WPN_DRAGOON_LANCE   */
  { "Dragoon Lance", WTYPE_SPEAR, 80, 40, ELEM_HOLY, WFLAG_NONE, 0, SINF_NONE, EQUIP_KAIN, 0xFFFF, 0xFFFF },
  /* WPN_OBELISK         */
  { "Obelisk", WTYPE_SPEAR, 85, 40, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_SPEARUSERS, 35000, 17500 },
  /* WPN_BLOOD_LANCE     */
  { "Blood Lance", WTYPE_SPEAR, 88, -28, ELEM_NONE, WFLAG_HP_DRAIN, 0, SINF_NONE, EQUIP_SPEARUSERS, 0xFFFF, 18000 },
  /* WPN_GUNGNIR         */
  { "Gungnir", WTYPE_SPEAR, 99, 30, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_SPEARUSERS, 0xFFFF, 0xFFFF },
  /* WPN_WYVERN_LANCE    */
  { "Wyvern Lance", WTYPE_SPEAR, 110, 30, ELEM_NONE, WFLAG_ANTI_DRAGON, 0, SINF_NONE, EQUIP_SPEARUSERS, 0xFFFF, 0xFFFF },
  /* WPN_HOLY_LANCE      */
  { "Holy Lance", WTYPE_SPEAR, 140, 30, ELEM_HOLY, WFLAG_CASTS_SPELL, 51, SINF_NONE, EQUIP_SPEARUSERS, 0xFFFF, 0xFFFF },


                      /* ==================== BOOMERANGS ==================== */

  /* WPN_BOOMERANG       */
  { "Boomerang", WTYPE_BOOMERANG, 8, 30, ELEM_NONE, WFLAG_LONG_RANGE|WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_NINJA, 150, 75 },
  /* WPN_METAL_BOOMERANG */
  { "Metal Boomerang", WTYPE_BOOMERANG, 16, 35, ELEM_NONE, WFLAG_LONG_RANGE|WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_NINJA, 800, 400 },
  /* WPN_CHAKRAM         */
  { "Chakram", WTYPE_BOOMERANG, 24, 30, ELEM_NONE, WFLAG_LONG_RANGE|WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_NINJA, 4000, 2000 },
  /* WPN_WING_EDGE       */
  { "Wing Edge", WTYPE_BOOMERANG, 32, 30, ELEM_NONE, WFLAG_LONG_RANGE|WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_NINJA, 6800, 3400 },
  /* WPN_MOONRING_BLADE  */
  { "Moonring Blade", WTYPE_BOOMERANG, 40, 35, ELEM_NONE, WFLAG_LONG_RANGE|WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_NINJA, 0xFFFF, 8000 },
  /* WPN_RISING_SUN      */
  { "Rising Sun", WTYPE_BOOMERANG, 50, 50, ELEM_NONE, WFLAG_LONG_RANGE|WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_NINJA, 0xFFFF, 0xFFFF },


                        /* ==================== DAGGERS ==================== */

  /* WPN_KNIFE           */
  { "Knife", WTYPE_DAGGER, 7, 50, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_DAGGERUSERS, 0xFFFF, 5 },
  /* WPN_DAGGER          */
  { "Dagger", WTYPE_DAGGER, 12, 40, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_DAGGERUSERS, 300, 150 },
  /* WPN_MYTHRIL_KNIFE   */
  { "Mythril Knife", WTYPE_DAGGER, 20, 40, ELEM_NONE, WFLAG_ANTI_GHOST|WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_DAGGERUSERS, 3000, 1500 },
  /* WPN_DANCING_DAGGER  */
  { "Dancing Dagger", WTYPE_DAGGER, 28, 40, ELEM_NONE, WFLAG_DMGONUSE, 0, SINF_NONE, EQUIP_DAGGERUSERS, 0xFFFF, 3000 },
  /* WPN_MAGE_MASHER     */
  { "Mage Masher", WTYPE_DAGGER, 35, 40, ELEM_NONE, WFLAG_ANTI_MAGE, 0, SINF_NONE, EQUIP_DAGGERUSERS, 3000, 1500 },
  /* WPN_TRITON_DAGGER   */
  { "Triton's Dagger", WTYPE_DAGGER, 62, 40, ELEM_WATER, WFLAG_CASTS_SPELL, 19, SINF_NONE, EQUIP_DAGGERUSERS, 0xFFFF, 15000 },
  /* WPN_ASSASSIN_DAGGER */
  { "Assassin's Dagger", WTYPE_DAGGER, 85, 40, ELEM_NONE, WFLAG_INSTANT_KO, 0, SINF_DEATH, EQUIP_DAGGERUSERS, 0xFFFF, 20000 },
  /* WPN_PHASE_CUTTER    */
  { "Phase Cutter", WTYPE_DAGGER, 150, 50, ELEM_NONE, WFLAG_ANTI_MECH|WFLAG_ANTI_GIANT, 0, SINF_NONE, EQUIP_CALCA|EQUIP_BRINA, 0xFFFF, 0xFFFF },


                      /* ==================== KATANAS ==================== */

  /* WPN_KUNAI           */
  { "Kunai", WTYPE_KATANA, 7, 40, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_NINJA, 200, 100 },
  /* WPN_KODACHI         */
  { "Kodachi", WTYPE_KATANA, 14, 40, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_NINJA, 350, 175 },
  /* WPN_KOGARASU        */
  { "Kogarasu", WTYPE_KATANA, 20, 40, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_NINJA, 0xFFFF, 2000 },
  /* WPN_CRIMSON_CHERRY  */
  { "Crimson Cherry", WTYPE_KATANA, 26, 40, ELEM_FIRE, WFLAG_NONE, 0, SINF_NONE, EQUIP_NINJA, 4800, 2400 },
  /* WPN_ASHURA          */
  { "Ashura", WTYPE_KATANA, 32, 40, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_NINJA, 7000, 3500 },
  /* WPN_BOLTSLICER      */
  { "Boltslicer", WTYPE_KATANA, 35, 40, ELEM_THUNDER, WFLAG_NONE, 0, SINF_NONE, EQUIP_NINJA, 0xFFFF, 4000 },
  /* WPN_KOTETSU         */
  { "Kotetsu", WTYPE_KATANA, 40, 40, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_NINJA, 0xFFFF, 5000 },
  /* WPN_KIKU_ICHIMONJI  */
  { "Kiku-ichimonji", WTYPE_KATANA, 48, 40, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_NINJA, 0xFFFF, 8000 },
  /* WPN_MURASAME        */
  { "Murasame", WTYPE_KATANA, 55, 40, ELEM_NONE, WFLAG_CASTS_SPELL, 10, SINF_NONE, EQUIP_NINJA, 0xFFFF, 12000 },
  /* WPN_MASAMUNE        */
  { "Masamune", WTYPE_KATANA, 65, 40, ELEM_NONE, WFLAG_CASTS_SPELL, 15, SINF_NONE, EQUIP_NINJA, 0xFFFF, 0xFFFF },
  /* WPN_MUTSUNOKAMI     */
  { "Mutsunokami", WTYPE_KATANA, 75, 40, ELEM_NONE, WFLAG_CASTS_SPELL, 16, SINF_NONE, EQUIP_NINJA, 0xFFFF, 0xFFFF },


                      /* ==================== AXES ==================== */

  /* WPN_CRESCENT_AXE    */
  { "Crescent Axe", WTYPE_AXE, 30, 20, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_AXEUSERS, 800, 400 },
  /* WPN_BATTLE_AXE      */
  { "Battle Axe", WTYPE_AXE, 42, 25, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_AXEUSERS, 2500, 1250 },
  /* WPN_TOMAHAWK        */
  { "Tomahawk", WTYPE_AXE, 50, 30, ELEM_NONE, WFLAG_THROWABLE|WFLAG_LONG_RANGE, 0, SINF_NONE, EQUIP_AXEUSERS, 0xFFFF, 6000 },
  /* WPN_DWARVEN_AXE     */
  { "Dwarven Axe", WTYPE_AXE, 62, 19, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_AXEUSERS, 15000, 7500 },
  /* WPN_OGREKILLER      */
  { "Ogrekiller", WTYPE_AXE, 80, 19, ELEM_NONE, WFLAG_ANTI_GIANT, 0, SINF_NONE, EQUIP_AXEUSERS, 0xFFFF, 18000 },
  /* WPN_POISON_AXE      */
  { "Poison Axe", WTYPE_AXE, 95, 10, ELEM_NONE, WFLAG_TWO_HANDED|WFLAG_CASTS_SPELL, 7, SINF_POISON, EQUIP_AXEUSERS, 0xFFFF, 22000 },
  /* WPN_RUNE_AXE        */
  { "Rune Axe", WTYPE_AXE, 100, 10, ELEM_NONE, WFLAG_TWO_HANDED|WFLAG_ANTI_MAGE, 0, SINF_NONE, EQUIP_AXEUSERS, 0xFFFF, 25000 },
  /* WPN_GIGANT_AXE      */
  { "Gigant Axe", WTYPE_AXE, 150, 25, ELEM_NONE, WFLAG_TWO_HANDED, 0, SINF_NONE, EQUIP_AXEUSERS, 0xFFFF, 0xFFFF },


                      /* ==================== HAMMERS ==================== */

  /* WPN_HAMMER          */
  { "Hammer", WTYPE_HAMMER, 20, 30, ELEM_NONE, WFLAG_TWO_HANDED|WFLAG_ANTI_MECH, 0, SINF_NONE, EQUIP_HAMMERS, 0xFFFF, 500 },
  /* WPN_WOODEN_HAMMER   */
  { "Wooden Hammer", WTYPE_HAMMER, 45, 25, ELEM_NONE, WFLAG_TWO_HANDED|WFLAG_ANTI_MECH, 0, SINF_NONE, EQUIP_HAMMERS, 0xFFFF, 2500 },
  /* WPN_MYTHRIL_HAMMER  */
  { "Mythril Hammer", WTYPE_HAMMER, 55, 25, ELEM_NONE, WFLAG_TWO_HANDED|WFLAG_ANTI_MECH|WFLAG_ANTI_GHOST, 0, SINF_NONE, EQUIP_HAMMERS, 8000, 4000 },
  /* WPN_GAIA_HAMMER     */
  { "Gaia Hammer", WTYPE_HAMMER, 65, 25, ELEM_FIRE, WFLAG_TWO_HANDED|WFLAG_ANTI_MECH|WFLAG_CASTS_SPELL, 17, SINF_NONE, EQUIP_HAMMERS, 12000, 6000 },
  /* WPN_SLEDGEHAMMER    */
  { "Sledgehammer", WTYPE_HAMMER, 90, 30, ELEM_NONE, WFLAG_TWO_HANDED|WFLAG_ANTI_MECH, 0, SINF_NONE, EQUIP_HAMMERS, 32000, 16000 },
  /* WPN_THOR_HAMMER     */
  { "Thor's Hammer", WTYPE_HAMMER, 140, 30, ELEM_THUNDER, WFLAG_TWO_HANDED|WFLAG_ANTI_MECH|WFLAG_CASTS_SPELL, 18, SINF_NONE, EQUIP_HAMMERS, 0xFFFF, 0xFFFF },


                      /* ==================== HARPS ==================== */

  /* WPN_DREAM_HARP      */
  { "Dream Harp", WTYPE_HARP, 8, 35, ELEM_NONE, WFLAG_LONG_RANGE, 0, SINF_NONE, EQUIP_EDWARD, 480, 240 },
  /* WPN_SILVER_HARP     */
  { "Silver Harp", WTYPE_HARP, 15, 35, ELEM_NONE, WFLAG_LONG_RANGE|WFLAG_ANTI_GHOST, 0, SINF_NONE, EQUIP_EDWARD, 880, 440 },
  /* WPN_LAMIA_HARP      */
  { "Lamia Harp", WTYPE_HARP, 18, 40, ELEM_NONE, WFLAG_LONG_RANGE, 0, SINF_CONFUSE, EQUIP_EDWARD, 0xFFFF, 2000 },
  /* WPN_DARK_HARP       */
  { "Dark Harp", WTYPE_HARP, 25, 40, ELEM_NONE, WFLAG_LONG_RANGE, 0, SINF_BLIND, EQUIP_EDWARD, 2800, 1400 },
  /* WPN_MUSE_HARP       */
  { "Muse Harp", WTYPE_HARP, 35, 40, ELEM_HOLY, WFLAG_LONG_RANGE|WFLAG_ANTI_GHOST|WFLAG_ANTI_DEMON, 0, SINF_NONE, EQUIP_EDWARD, 6500, 3250 },
  /* WPN_APOLLOS_HARP    */
  { "Apollo's Harp", WTYPE_HARP, 60, 40, ELEM_FIRE, WFLAG_LONG_RANGE|WFLAG_ANTI_DRAGON, 0, SINF_NONE, EQUIP_EDWARD, 0xFFFF, 0xFFFF },
  /* WPN_LOKIS_HARP      */
  { "Loki's Harp", WTYPE_HARP, 98, 99, ELEM_NONE, WFLAG_LONG_RANGE, 0, SINF_NONE, EQUIP_EDWARD, 0xFFFF, 0xFFFF },


                        /* ==================== BOWS ==================== */

  /* WPN_BOW             */
  { "Bow", WTYPE_BOW, 10, 25, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_BOWUSERS, 220, 110 },
  /* WPN_CROSSBOW        */
  { "Crossbow", WTYPE_BOW, 20, 25, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_BOWUSERS, 700, 350 },
  /* WPN_GREAT_BOW       */
  { "Great Bow", WTYPE_BOW, 30, 25, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_BOWUSERS, 2000, 1000 },
  /* WPN_KILLER_BOW      */
  { "Killer Bow", WTYPE_BOW, 40, 25, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_BOWUSERS, 3000, 1500 },
  /* WPN_ELFIN_BOW       */
  { "Elfin Bow", WTYPE_BOW, 50, 25, ELEM_NONE, WFLAG_THROWABLE|WFLAG_CASTS_SPELL, 52, SINF_NONE, EQUIP_BOWUSERS, 5000, 2500 },
  /* WPN_YOICHI_BOW      */
  { "Yoichi's Bow", WTYPE_BOW, 60, 25, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_BOWUSERS, 0xFFFF, 0xFFFF },
  /* WPN_ARTEMIS_BOW     */
  { "Artemis's Bow", WTYPE_BOW, 80, 25, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_BOWUSERS, 0xFFFF, 0xFFFF },
  /* WPN_PERSEUS_BOW     */
  { "Perseus's Bow", WTYPE_BOW, 90, 25, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_BOWUSERS, 0xFFFF, 0xFFFF },


                      /* ==================== ARROWS ==================== */

  /* WPN_MEDUSA_ARROWS   */
  { "Medusa Arrows", WTYPE_ARROW, 1, 0, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_GRADPETRIFY, EQUIP_BOWUSERS, 0xFFFF, 1 },
  /* WPN_IRON_ARROWS     */
  { "Iron Arrows", WTYPE_ARROW, 5, 0, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_BOWUSERS, 50, 25 },
  /* WPN_HOLY_ARROWS     */
  { "Holy Arrows", WTYPE_ARROW, 10, 0, ELEM_HOLY, WFLAG_THROWABLE|WFLAG_ANTI_GHOST, 0, SINF_NONE, EQUIP_BOWUSERS, 500, 250 },
  /* WPN_FIRE_ARROWS     */
  { "Fire Arrows", WTYPE_ARROW, 15, 0, ELEM_FIRE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_BOWUSERS, 500, 250 },
  /* WPN_ICE_ARROWS      */
  { "Ice Arrows", WTYPE_ARROW, 15, 0, ELEM_ICE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_BOWUSERS, 500, 250 },
  /* WPN_LIGHTNING_ARROWS*/
  { "Lightning Arrows", WTYPE_ARROW, 15, 0, ELEM_THUNDER, WFLAG_THROWABLE|WFLAG_ANTI_MECH, 0, SINF_NONE, EQUIP_BOWUSERS, 500, 250 },
  /* WPN_BLINDING_ARROWS */
  { "Blinding Arrows", WTYPE_ARROW, 20, 0, ELEM_DARK, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_BOWUSERS, 1000, 500 },
  /* WPN_POISON_ARROWS   */
  { "Poison Arrows", WTYPE_ARROW, 30, 0, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_POISON, EQUIP_BOWUSERS, 0xFFFF, 10 },
  /* WPN_SILENCING_ARROWS*/
  { "Silencing Arrows", WTYPE_ARROW, 35, 0, ELEM_NONE, WFLAG_THROWABLE|WFLAG_ANTI_MAGE, 0, SINF_SILENCE, EQUIP_BOWUSERS, 1000, 500 },
  /* WPN_ANGEL_ARROWS    */
  { "Angel Arrows", WTYPE_ARROW, 40, 0, ELEM_NONE, WFLAG_THROWABLE|WFLAG_ANTI_GIANT, 0, SINF_NONE, EQUIP_BOWUSERS, 0xFFFF, 500 },
  /* WPN_YOICHI_ARROWS   */
  { "Yoichi's Arrows", WTYPE_ARROW, 50, 0, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_BOWUSERS, 0xFFFF, 0xFFFF },
  /* WPN_ARTEMIS_ARROWS  */
  { "Artemis's Arrows", WTYPE_ARROW, 75, 0, ELEM_NONE, WFLAG_THROWABLE|WFLAG_ANTI_DRAGON, 0, SINF_NONE, EQUIP_BOWUSERS, 0xFFFF, 0xFFFF },
  /* WPN_PERSEUS_ARROWS  */
  { "Perseus's Arrows", WTYPE_ARROW, 80, 0, ELEM_NONE, WFLAG_THROWABLE|WFLAG_ANTI_GIANT, 0, SINF_NONE, EQUIP_BOWUSERS, 0xFFFF, 0xFFFF },


                      /* ==================== WHIPS ==================== */

  /* WPN_QUEENS_WHIP     */
  { "Queen's Whip", WTYPE_WHIP, 5, 40, ELEM_NONE, WFLAG_LONG_RANGE, 0, SINF_NONE, EQUIP_ROSA|EQUIP_RYDIA|EQUIP_POROM|EQUIP_LUCA|EQUIP_URSULA|EQUIP_LEONORA|EQUIP_IZAYOI|EQUIP_HARLEY, 6800, 3400 },
  /* WPN_WHIP            */
  { "Whip", WTYPE_WHIP, 10, 0, ELEM_NONE, WFLAG_LONG_RANGE, 0, SINF_NONE, EQUIP_WHIPUSERS, 200, 100 },
  /* WPN_THORN_WHIP      */
  { "Thorn Whip", WTYPE_WHIP, 20, 0, ELEM_NONE, WFLAG_LONG_RANGE, 0, SINF_NONE, EQUIP_WHIPUSERS, 3000, 1500 },
  /* WPN_CHAIN_WHIP      */
  { "Chain Whip", WTYPE_WHIP, 30, 5, ELEM_NONE, WFLAG_LONG_RANGE, 0, SINF_NONE, EQUIP_WHIPUSERS, 6000, 3000 },
  /* WPN_ICE_WHIP        */
  { "Ice Whip", WTYPE_WHIP, 38, 15, ELEM_ICE, WFLAG_LONG_RANGE, 0, SINF_NONE, EQUIP_WHIPUSERS, 0xFFFF, 6000 },
  /* WPN_BLITZ_WHIP      */
  { "Blitz Whip", WTYPE_WHIP, 40, 10, ELEM_THUNDER, WFLAG_LONG_RANGE, 0, SINF_NONE, EQUIP_WHIPUSERS, 10000, 5000 },
  /* WPN_FLAME_WHIP      */
  { "Flame Whip", WTYPE_WHIP, 50, 15, ELEM_FIRE, WFLAG_LONG_RANGE, 0, SINF_NONE, EQUIP_WHIPUSERS, 0xFFFF, 12000 },
  /* WPN_DRAGON_WHISKER  */
  { "Dragon Whisker", WTYPE_WHIP, 55, 25, ELEM_NONE, WFLAG_LONG_RANGE|WFLAG_ANTI_DRAGON, 0, SINF_NONE, EQUIP_WHIPUSERS, 0xFFFF, 15000 },
  /* WPN_MYSTIC_WHIP     */
  { "Mystic Whip", WTYPE_WHIP, 100, 25, ELEM_HOLY, WFLAG_LONG_RANGE, 0, SINF_NONE, EQUIP_WHIPUSERS, 0xFFFF, 0xFFFF },


                      /* ==================== SHURIKEN ==================== */

  /* WPN_SHURIKEN        */
  { "Shuriken", WTYPE_SHURIKEN, 20, 0, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_EDGE|EQUIP_GEKKOU, 200, 1 },
  /* WPN_MANJI_SHURIKEN  */
  { "Manji Shuriken", WTYPE_SHURIKEN, 40, 0, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_EDGE|EQUIP_GEKKOU, 20000, 1 },
  /* WPN_FUMA_SHURIKEN   */
  { "Fuma Shuriken", WTYPE_SHURIKEN, 80, 0, ELEM_NONE, WFLAG_THROWABLE, 0, SINF_NONE, EQUIP_EDGE|EQUIP_GEKKOU, 50000, 1 },

                      /* ==================== FISTS ==================== */

  /* WPN_UNARMED         */
  { "Unarmed", WTYPE_FISTS, 1, 50, ELEM_NONE, WFLAG_NONE, 0, SINF_NONE, EQUIP_EVERYONE, 0xFFFF, 0 },
};

const u16 weapon_count = WEAPON_COUNT;