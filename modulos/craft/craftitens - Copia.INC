
#define MAX_CRAFT_ITENS   (15)
#define MAX_RECIPES       (4)

enum e_craft
{
	E_CRAFT_ITEM_NAME[45],
	E_CRAFT_ITEM_TYPE,
	E_CRAFT_ITEM_MODEL,
	E_CRAFT_ITEM_QUANTIA,
bool:
	E_CRAFT_ITEM_RESET,
}

new g_ServerItemCraft[MAX_CRAFT_ITENS][e_craft];
new g_ServerItemRecipe[MAX_CRAFT_ITENS][MAX_RECIPES][e_craft];

new
	g_ServerPoolSizeCraft
	;


stock AddCraftableItem(itemname[], itemtype, itemmodel, itemquantia)
{
    format(g_ServerItemCraft[g_ServerPoolSizeCraft][E_CRAFT_ITEM_NAME], 45, itemname);
    g_ServerItemCraft[g_ServerPoolSizeCraft][E_CRAFT_ITEM_TYPE] = itemtype;
    g_ServerItemCraft[g_ServerPoolSizeCraft][E_CRAFT_ITEM_MODEL] = itemmodel;
    g_ServerItemCraft[g_ServerPoolSizeCraft][E_CRAFT_ITEM_QUANTIA] = itemquantia;

	for (new g_recipe; g_recipe < MAX_RECIPES; g_recipe++)
	{
	    format(g_ServerItemRecipe[g_ServerPoolSizeCraft][E_CRAFT_ITEM_NAME], 45, "INVALID");
	    g_ServerItemRecipe[g_ServerPoolSizeCraft][E_CRAFT_ITEM_TYPE] = -1;
	    g_ServerItemRecipe[g_ServerPoolSizeCraft][E_CRAFT_ITEM_MODEL] = -1;
	    g_ServerItemRecipe[g_ServerPoolSizeCraft][E_CRAFT_ITEM_QUANTIA] = -1;
	    g_ServerItemRecipe[g_ServerPoolSizeCraft][E_CRAFT_ITEM_RESET] = false;
	}

    g_ServerPoolSizeCraft ++;
}

stock AddRecipe(itemname[], itemtype, itemmodel, itemquantia, bool:itemreset)
{
	for (new g_recipe; g_recipe < MAX_RECIPES; g_recipe++)
	{
	    if (g_ServerItemRecipe[g_ServerPoolSizeCraft][E_CRAFT_ITEM_TYPE] == -1)
	    {
		    format(g_ServerItemRecipe[g_ServerPoolSizeCraft][E_CRAFT_ITEM_NAME], 45, itemname);
		    g_ServerItemRecipe[g_ServerPoolSizeCraft][E_CRAFT_ITEM_TYPE] = itemtype;
		    g_ServerItemRecipe[g_ServerPoolSizeCraft][E_CRAFT_ITEM_MODEL] = itemmodel;
		    g_ServerItemRecipe[g_ServerPoolSizeCraft][E_CRAFT_ITEM_QUANTIA] = itemquantia;
		    g_ServerItemRecipe[g_ServerPoolSizeCraft][E_CRAFT_ITEM_RESET] = itemreset;
		}
	}
}

stock InitServerCraftingItens()
{
    AddCraftableItem("Bandagem", ITEM_TYPE_BANDAGE, 2324, 2);
    AddRecipe("Roupa", 	ITEM_TYPE_SKIN, 	2584, 1, .itemreset = true);
    AddRecipe("Faca", 	ITEM_TYPE_WEAPON, 	2584, 1, .itemreset = false);
    
    AddCraftableItem("Bandagem", ITEM_TYPE_BANDAGE, 2324, 2);
    AddRecipe("Roupa", 	ITEM_TYPE_SKIN, 	2584, 1, .itemreset = true);
    AddRecipe("Faca", 	ITEM_TYPE_WEAPON, 	2584, 1, .itemreset = false);
    
    AddCraftableItem("Bandagem", ITEM_TYPE_BANDAGE, 2324, 2);
    AddRecipe("Roupa", 	ITEM_TYPE_SKIN, 	2584, 1, .itemreset = true);
    AddRecipe("Faca", 	ITEM_TYPE_WEAPON, 	2584, 1, .itemreset = false);
    
    AddCraftableItem("Bandagem", ITEM_TYPE_BANDAGE, 2324, 2);
    AddRecipe("Roupa", 	ITEM_TYPE_SKIN, 	2584, 1, .itemreset = true);
    AddRecipe("Faca", 	ITEM_TYPE_WEAPON, 	2584, 1, .itemreset = false);
}





