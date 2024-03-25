#include <stdio.h>

int total=0;

int search_reach (int *a, int *answer_a, int *kakutei, int *sum, int n) {
  int i,j,k;
  return 0;
}

int solved_answer (int *a, int *answer_a, int *kakutei, int *sum, int n,
		   int *index, int **member) {
  int ans=0;
  int i,j,k;
  for (j=0; j<n; j++)
    for (i=0; i<n; i++) {
      if (a[j*n+i] == 0) {
	if (total) {
	  search_reach(a, answer_a, kakutei, sum, n);
	  for (k=0; k<4; k++) {
	    int idx;
	    if ((idx = index[k*n*n+j*n+i]) != -1) {
	      if (kakutei[idx] == n-1) {
		printf("index: %d reached\n", idx);
		answer_a[j*n+i] = total-sum[idx];
		ans++;
	      }
	    }
	  }
	} else {
	  search_reach(a, answer_a, kakutei, sum, n);
	  for (k=0; k<4; k++) {
	    int idx;
	    if ((idx = index[k*n*n+j*n+i]) != -1) {
	      if (kakutei[idx] == n-1) {
		printf("(%d,%d) index: %d reached\n", i, j, idx);
		for (int kk=0; kk<n; kk++) {
		  int idx2;
		  if ((idx2 = index[kk*n*n+j*n+i]) != -1) {
		    if (kakutei[idx2] == n-2) {
		      printf("choimuzu index:%d\n", idx2);
		      for (int l=0; l<n; l++) {
			if (*member[idx2*n+l] == 0 &&
			    member[idx2*n+l] != &a[j*n+i]
			    ) {
			  int diff = member[idx2*n+l]-&a[0];
			  printf("%d %d %d\n", l, diff, sum[idx]-sum[idx2]);
			  answer_a[diff] = sum[idx]-sum[idx2];
			  ans++;
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  return ans;
}

void update_kakutei(int *answer_a, int *kakutei, int *sum, int n) {
  int i, j;

  int *p;
  for (j=0; j<n; j++)
    for (i=0; i<n; i++) {
      p = &answer_a[j*n+i];
      sum[n+i] += *p;
      sum[j] += *p;
      if (i == j) sum[2*n] += *p;
      if (i+j == n - 1) sum[2*n+1] += *p;
      if (*p) {
	kakutei[n+i]++;
	kakutei[j]++;
	if (i == j) kakutei[2*n]++;
	if (i+j == n - 1) kakutei[2*n+1]++;
      }
    }
  if (total == 0)
    for (int k=0; k<2*n+2; k++)
      if (kakutei[k] == n)
	total = sum[k];
}

void print_kakutei (int *a, int *kakutei, int *sum, int n) {
  int i, j;

  for (j=0; j<n; j++)
    for (i=0; i<n; i++)
      printf("%d%s", a[j*n+i], i == n-1 ? "\n" : " ");

  for (int k=0; k<2*n+2; k++)
    printf("%d, %d\n", kakutei[k], sum[k]);
}

int main(void) {
  int i,j,k;
  int n;
  scanf("%d",&n);

  int a[n][n];
  int answer_a[n][n];
  for (j=0; j<n; j++)
    for (i=0; i<n; i++)
      a[j][i] = answer_a[j][i] = 0;
  int kakutei[2*n+2];
  int sum[2*n+2];
  for (k=0; k<2*n+2; k++)
    kakutei[k] = sum[k] = 0;

  int index[4][n][n];
  for (j=0; j<n; j++)
    for (i=0; i<n; i++) {
      index[0][j][i] = j;
      index[1][j][i] = i+n;
      index[2][j][i] = i == j ? 2*n : -1;
      index[3][j][i] = i+j == n-1 ? 2*n+1 : -1;
    }
  int *member[2*n+2][n];
  for (j=0; j<n; j++)
    for (i=0; i<n; i++) {
      member[j][i] = &a[j][i];
      member[i+n][j] = &a[j][i];
      if (i == j) member[2*n][i] = &a[j][i];
      if (i+j == n-1) member[2*n+1][j] = &a[j][i];
    }

  for (j=0; j<n; j++)
    for (i=0; i<n; i++)
      scanf("%d", &answer_a[j][i]);

  update_kakutei(answer_a[0], kakutei, sum, n);
  for (j=0; j<n; j++)
    for (i=0; i<n; i++)
      if (answer_a[j][i]) {
	a[j][i] = answer_a[j][i];
	answer_a[j][i] = 0;
      }
  while (solved_answer(a[0],answer_a[0],kakutei,sum,n,index[0][0],member[0])) {
    update_kakutei(answer_a[0], kakutei, sum, n);
    for (j=0; j<n; j++)
      for (i=0; i<n; i++)
	if (answer_a[j][i]) {
	  a[j][i] = answer_a[j][i];
	  answer_a[j][i] = 0;
	}
    print_kakutei(a[0], kakutei, sum, n);
  }

  return 0;
}
