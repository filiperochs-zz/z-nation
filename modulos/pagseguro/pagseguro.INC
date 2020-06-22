

#include <a_samp>
#include <a_http>


// keliani.math@hotmail.com
// FA99F796E18547C084701B339851FD43


#define ArquivoPHP 		 "znation-dayz.esy.es/transacao.php"
#define EmailPagSeguro   "e-mail@gmail.com"
#define TokenPagSeguro   "ABCDEFGH"

enum psEnumPlayer {

	PS_CODE[144],
	PS_ITEM[75],
	PS_STATUS,
	PS_CASH,
	PS_CASH_BONUS,
}

enum ArrayCodeEnum {

	code_method,
	code_method_name[55],
}

new PS_Player[MAX_PLAYERS][psEnumPlayer];

static const psStatus[][] = {

	{ "{FF3300}STATUS DESCONHECIDO"  },
	{ "{AAAAAA}AGUARDANDO PAGAMENTO" },
	{ "{FFFF55}PAGAMENTO EM ANÁLISE" },
	{ "{00CC00}PAGAMENTO EFETUADO" 	 },
	{ "{00CC00}PAGAMENTO DISPONÍVEL" },
	{ "{FF0000}PAGAMENTO EM DISPUTA" },
	{ "{FF7700}PAGAMENTO DEVOLVIDO"  },
	{ "{FF0000}PAGAMENTO CANCELADO"  }
};

static const psMetodo[][] = {

	{ "Desconhecida" 		},
	{ "Cartão de crédito" 	},
	{ "Boleto Bancário" 	},
	{ "Débito online (TEF)" },
	{ "Saldo PagSeguro" 	},
	{ "Oi Paggo" 			},
	{ "Depósito em conta" 	}
};

static const ArrayMethodCode[][ArrayCodeEnum] = {
	{ 101,	"Cartão de crédito Visa."			  	},
	{ 102,	"Cartão de crédito MasterCard."			},
	{ 103,	"Cartão de crédito American Express."	},
	{ 104,	"Cartão de crédito Diners."				},
	{ 105,	"Cartão de crédito Hipercard."			},
	{ 106,	"Cartão de crédito Aura."				},
	{ 107,	"Cartão de crédito Elo."				},
	{ 108,	"Cartão de crédito PLENOCard."			},
	{ 109,	"Cartão de crédito PersonalCard."		},
	{ 110,	"Cartão de crédito JCB."				},
	{ 111,	"Cartão de crédito Discover."			},
	{ 112,	"Cartão de crédito BrasilCard."			},
	{ 113,	"Cartão de crédito FORTBRASIL."			},
	{ 114,	"Cartão de crédito CARDBAN."			},
	{ 115,	"Cartão de crédito VALECARD."			},
	{ 116,	"Cartão de crédito Cabal."				},
	{ 117,	"Cartão de crédito Mais!."				},
	{ 118,	"Cartão de crédito Avista."				},
	{ 119,	"Cartão de crédito GRANDCARD."			},
	{ 120,	"Cartão de crédito Sorocred."			},
	{ 201,	"Boleto Bradesco."						},
	{ 202,	"Boleto Santander."						},
	{ 301,	"Débito online Bradesco."				},
	{ 302,	"Débito online Itaú."					},
	{ 303,	"Débito online Unibanco."				},
	{ 304,	"Débito online Banco do Brasil."		},
	{ 305,	"Débito online Banco Real."				},
	{ 306,	"Débito online Banrisul."				},
	{ 307,	"Débito online HSBC."					},
	{ 401,	"Saldo PagSeguro."						},
	{ 501,	"Oi Paggo."								},
	{ 701,	"Depósito em conta - Banco do Brasil"	},
	{ 702,	"Depósito em conta - HSBC"				}
};

stock GetMethodCode(code) {

	new methodcode[55] = "Nenhum";

	for(new index; index < sizeof (ArrayMethodCode); index++) {
	    if (code == ArrayMethodCode[index][code_method]) {
	        format(methodcode, sizeof (methodcode), ArrayMethodCode[index][code_method_name]); break;
	    }
	}
	return methodcode;
}

stock checkCodigoTransacao(playerid, code[]) {

	new string[200];
	format(string, sizeof (string), pastaPagseguro, code);
	if (fexist(string)) {
	    SendClientMessage(playerid, corError, "ERRO: {999999}Este código de transação já foi ativado por outro jogador!");
	    return 1;
	}

    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", "\n {AAAAAA}AGUARDE ENQUANTO O SERVIDOR PEGA AS INFORMAÇÕES DO PAGSEGURO...\n", "Aguardar..", "");

    PS_Player[playerid][PS_CASH] = 0;
    PS_Player[playerid][PS_CASH_BONUS] = 0;
    format(PS_Player[playerid][PS_CODE], 144, code);

	new string_code[255] = "c=";
	strcat(string_code, code);
	strcat(string_code, "&e=");
	strcat(string_code, EmailPagSeguro);
	strcat(string_code, "&t=");
	strcat(string_code, TokenPagSeguro);
    HTTP(playerid, HTTP_POST, ArquivoPHP, string_code, "onKeyTransacaoCheck");
    
    return 1;
}

forward onKeyTransacaoCheck(index, response_code, data[]);
public onKeyTransacaoCheck(index, response_code, data[]) {

	if (strlen(data) < 700) {
	
	    ShowPlayerDialog(index, 0, DIALOG_STYLE_MSGBOX, " ", "\n {FF5500}CÓDIGO DE TRANSAÇÃO INVÁLIDO OU HOUVE UM ERRO EM NOSSA DATABASE\nPEÇA AJUDA AO ADMINISTRADOR RESPONSÁVEL!", "Fechar", "");
	    return 1;
	}

	new string[128], string_info[8][128];

	GetKeyTransacaoInfo(index, data, string_info[0],string_info[1],string_info[2],string_info[3],string_info[4],string_info[5],string_info[6],string_info[7]);

	stringGlobal[0] = EOS;
	
	strcat(stringGlobal, "{FFFFFF}DADOS DO COMPRADOR:\n");
	format(string, sizeof string, "{BBBBBB}Nome do comprador: {FFFFFF}%s\n", string_info[4]);
	strcat(stringGlobal, string);
	format(string, sizeof string, "{BBBBBB}E-mail do comprador: {FFFFFF}%s\n", string_info[5]);
	strcat(stringGlobal, string);
	
	strcat(stringGlobal, "{999999}\nDADOS DA TRANSAÇÃO:\n");
	format(string, sizeof string, "{BBBBBB}Código da transação: {FF5555}%s\n", string_info[6]);
	strcat(stringGlobal, string);
	format(string, sizeof string, "{BBBBBB}Status da transação: %s\n", string_info[0]);
	strcat(stringGlobal, string);
	format(string, sizeof string, "{BBBBBB}Nome do item: {FFFFFF}%s\n", string_info[3]);
	strcat(stringGlobal, string);
	format(string, sizeof string, "{BBBBBB}Custo do item: {FFFFFF}%s\n", string_info[2]);
	strcat(stringGlobal, string);
	format(string, sizeof string, "{BBBBBB}Tipo de pagamento: {FFFFFF}%s\n", string_info[1]);
	strcat(stringGlobal, string);
	format(string, sizeof string, "{BBBBBB}Meio de pagamento: {FFFFFF}%s\n", string_info[7]);
	strcat(stringGlobal, string);
	format(string, sizeof string, "{BBBBBB}Total de ZP: {AA0000}%d ZP\n", PS_Player[index][PS_CASH]);
	strcat(stringGlobal, string);

    strcat(stringGlobal, "{FFFFFF}\nVocê deseja ativar o ZP agora?\n\n");
    strcat(stringGlobal, "{AAAAAA}OBS: Ao ativar o ZP, não será mais possível ativar em outra conta com o mesmo código de transação.\n\
	É recomendado que você ative o quanto antes para que não ocorra problemas futuramente com o código.");

	ShowPlayerDialog(index, 76, DIALOG_STYLE_MSGBOX, "Ativação do seu ZP", stringGlobal, "ATIVAR", "Cancelar");

	return 1;
}

stock GetKeyTransacaoInfo(playerid, data[], status[], method[], custo[], itemname[], comprador[], email[], code[], methodcode[]) {

	new ps_Key		[25] = "nenhum";
	new ps_KeyData	[255];
	new ps_Pos;

	// Código de transação
	ps_Key = "<code>";ps_Pos = strfind(data, ps_Key);
	if ( ps_Pos != -1 ) {

	    ps_Pos = (ps_Pos + strlen(ps_Key));

	    strmid(ps_KeyData, data, ps_Pos, strfind(data, "<", false, ps_Pos + 1), 255);
	    format(code, 144, ps_KeyData);
	}

	// Status da transação
	ps_Key = "<status>";ps_Pos = strfind(data, ps_Key);
	if ( ps_Pos != -1 ) {

	    ps_Pos = (ps_Pos + strlen(ps_Key));

	    strmid(ps_KeyData, data, ps_Pos, strfind(data, "<", false, ps_Pos + 1), 255);
	    format(status, 128, "%s", psStatus[strval(ps_KeyData)]);
	    
	    PS_Player[playerid][PS_STATUS] = strval(ps_KeyData);
	}

	// Método da transação
	ps_Key = "<paymentMethod>";ps_Pos = strfind(data, ps_Key);
	if ( ps_Pos != -1 ) {

	    ps_Pos = (ps_Pos + (strlen(ps_Key) + strlen("<type>")));

	    strmid(ps_KeyData, data, ps_Pos, strfind(data, "<", false, ps_Pos + 1), 255);
	    format(method, 128, "%s", psMetodo[strval(ps_KeyData)]);
	}

	// Custo do item
	ps_Key = "<grossAmount>";ps_Pos = strfind(data, ps_Key);
	if ( ps_Pos != -1 ) {

	    ps_Pos = (ps_Pos + strlen(ps_Key));

	    strmid(ps_KeyData, data, ps_Pos, strfind(data, "<", false, ps_Pos + 1), 255);
	    format(custo, 128, "{00BB00}R${AAFFAA}%s", ps_KeyData);
	    
	    PS_Player[playerid][PS_CASH] = strval(ps_KeyData) * 1000;
	}

	// Nome do item
	ps_Key = "<description>";ps_Pos = strfind(data, ps_Key);
	if ( ps_Pos != -1 ) {

	    ps_Pos = (ps_Pos + strlen(ps_Key));

	    strmid(ps_KeyData, data, ps_Pos, strfind(data, "<", false, ps_Pos + 1), 255);
	    format(itemname, 128, "%s", ps_KeyData);
	    format(PS_Player[playerid][PS_ITEM], 128, "%s", ps_KeyData);
	}
	
	// Nome do comprador
	ps_Key = "<name>";ps_Pos = strfind(data, ps_Key);
	if ( ps_Pos != -1 ) {

	    ps_Pos = (ps_Pos + strlen(ps_Key));

	    strmid(ps_KeyData, data, ps_Pos, strfind(data, "<", false, ps_Pos + 1), 255);
	    format(comprador, 128, "%s", ps_KeyData);
	}
	
	// E-mail do comprador
	ps_Key = "<email>";ps_Pos = strfind(data, ps_Key);
	if ( ps_Pos != -1 ) {

	    ps_Pos = (ps_Pos + strlen(ps_Key));

	    strmid(ps_KeyData, data, ps_Pos, strfind(data, "<", false, ps_Pos + 1), 255);
	    format(email, 128, "%s", ps_KeyData);
	}
	
	// Código do método de compra
	ps_Key = "</type><code>";ps_Pos = strfind(data, ps_Key);
	if ( ps_Pos != -1 ) {

	    ps_Pos = (ps_Pos + strlen(ps_Key));

	    strmid(ps_KeyData, data, ps_Pos, strfind(data, "<", false, ps_Pos + 1), 255);
	    format(methodcode, 128, "%s", GetMethodCode(strval(ps_KeyData)));
	}
}

stock GivePlayerKeyCash(playerid) {

	new string[200];
	
	format(string, sizeof (string), pastaPagseguro, PS_Player[playerid][PS_CODE]);
	
	if (!fexist(string)) {
	
	    if (PS_Player[playerid][PS_STATUS] != 3 && PS_Player[playerid][PS_STATUS] != 4) {
	        return SendClientMessage(playerid, corError, "ERRO: {999999}O pagamento ainda não foi confirmado, por isso ainda não é possível ativar seu cash."),
                   SendClientMessage(playerid, corError, "ERRO: {999999}O prazo para confirmação após o pagamento é de 3 dias úteis!");
	    }
	
	    DOF2_CreateFile(string);
	    DOF2_SetString(string, "ativador", getNome(playerid));
	    DOF2_SetString(string, "item", PS_Player[playerid][PS_ITEM]);
	    DOF2_SetInt(string, "cash", PS_Player[playerid][PS_CASH]);
	    new datef[45], date[6];
	    getdate(date[2], date[1], date[0]);
	    gettime(date[3], date[4], date[5]);
	    format(datef, sizeof (datef), "%d/%d/%d as %d:%d:%d",date[0],date[1],date[2],date[3],date[4],date[5]);
	    DOF2_SetString(string, "data", datef);
	    DOF2_SaveFile();
	    
	    PlayerData[playerid][dCoins] += (PS_Player[playerid][PS_CASH]);
	    
		format(string, sizeof (string), "%d ~r~~h~~h~ZP", PlayerData[playerid][dCoins]);
		PlayerTextDrawSetString(playerid, textPlayerZp, string);
	    
		stringGlobal[0] = EOS;

		strcat(stringGlobal, "{00CC00}* INFORMAÇÕES DA ATIVAÇÃO DO SEU CASH:\n\n");

		strcat(stringGlobal, "{999999}DADOS DO CÓDIGO:\n");
		format(string, sizeof string, "{AAAAAA}Código da transação: {00BB00}%s\n", PS_Player[playerid][PS_CODE]);
		strcat(stringGlobal, string);
		format(string, sizeof string, "{AAAAAA}Nome do item: {FFFFFF}%s\n", PS_Player[playerid][PS_ITEM]);
		strcat(stringGlobal, string);
		format(string, sizeof string, "{F5DEB3}ZP ADQUIRIDO: {AA0000}%d ZP\n", PS_Player[playerid][PS_CASH]);
		strcat(stringGlobal, string);
		format(string, sizeof string, "{F5DEB3}ZP BÔNUS: {AA0000}%d ZP\n", PS_Player[playerid][PS_CASH_BONUS]);
		strcat(stringGlobal, string);

	    strcat(stringGlobal, "{AAAAAA}OBS: A partir de agora este mesmo código não poderá mais ser reutilizado.");

		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Ativação do seu ZP", stringGlobal, "Informado", "");

		format(string, sizeof string, "* Você ativou %d de ZP em sua conta, utilize-os como quizer.", PS_Player[playerid][PS_CASH]);
	 	SendClientMessage(playerid, corInfo, string);
		Log::("cash", "%s activated %d, Key: %s", getNome(playerid), PS_Player[playerid][PS_CASH], PS_Player[playerid][PS_CODE]);

	    PS_Player[playerid][PS_CASH] = 0;
	    PS_Player[playerid][PS_CASH_BONUS] = 0;
	
	} else {
	    SendClientMessage(playerid, corError, "ERRO: {999999}Este código de transação já foi ativado por outro jogador!");
	}
	return 1;
}

stock ShowPlayerDialogKeyCash(playerid) {

	ShowPlayerDialog(playerid, 75, DIALOG_STYLE_INPUT, "Ativação de Z Points",
	"{CCCCCC}Ao realizar uma compra usando o {FF5555}PagSeguro{CCCCCC}, um e-mail é enviado para você.\n\
	Nele tem todas as informações da compra, inclusive o código de transação que você deverá usar aqui.\n\
	Exemplo de código: {FF5555}3F814540-17A5-2874-9D91-ZCA6FB405EF1\n\
	{FFFFFF}* Digite abaixo o código de transação do PagSeguro:\n\n\
	{CCCCCC}OBS: Caso o e-mail não esteja em sua caixa de entrada, verifique em sua {AAFFFF}Caixa de Spam (Lixo).",
	"Verificar", "Voltar");
}












