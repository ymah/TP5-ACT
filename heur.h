int *objet; /* liste des objets */
int nobjet; /* nbr des objets */
int *sac; /* liste des sacs */
int courant; 
int *res;
int cap;

void heuristiqueNonTrie();
int heuristique1(int *objet,int o_size,int *lsac,int cap_s);
int heuristique2(int *objet,int o_size,int *lsac,int cap_s);
int heuristique3(int *objet,int o_size,int *lsac,int cap_s);

void getData();
