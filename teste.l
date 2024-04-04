/* Coloque aqui definições regulares */

WS	[ \t\n]


%%
    /* Padrões e ações. Nesta seção, comentários devem ter um tab antes */

{WS}	{ /* ignora espaços, tabs e '\n' */ } 

.       { return *yytext; 
          /* Essa deve ser a última regra. Dessa forma qualquer caractere isolado será retornado pelo seu código ascii. */ }

%%

/* Não coloque nada aqui - a função main é automaticamente incluída na hora de avaliar e dar a nota. */