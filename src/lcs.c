/*
Title:
lcs.c
Summary:
A Longest Common Substructure Implementation
*/

int max (int a, int b){ 
  if (a > b){ 
    return a; 
  } else { 
    return b; 
  } 
}

int lcs(char *input, char *dic_ref, int ind_inp, int ind_dic_ref){
  int matrix[ind_inp + 1][ind_dic_ref +1];
  int i;
  int j;
  for (i = 0; i <= ind_inp; i++){
    for (j = 0; j <= ind_dic_ref; j++){
      if ( i == 0 || j == 0){
        matrix[i][j] = 0;
      } else if ( input[i-1] == dic_ref[j-1] ) {
          matrix[i][j] = matrix[i-1][j-1] + 1;
      } else {
          matrix[i][j] = max( matrix[i-1][j], matrix[i][j-1]);
      }
    }
  }
  return matrix[ind_inp][ind_dic_ref];
}

