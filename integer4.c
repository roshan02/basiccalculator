#define PLUS 1
#define MINUS -1 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node {
	int num;
	int flag;
	struct node *next, *prev;
}node;

typedef struct list {
	node *head, *tail;
	int len, dec, sign;
}list;
void init(list *l);
void insert(list *l, int pos, int num);
int remov(list *l, int pos);
void traverse(list *l);
void append(list *l, int num);
int length(list *l);

void init(list *l){
	l->head = l->tail = NULL;
	l->len = 0;
	l->dec = 0;
	l->sign = 1;
}
void insert(list *l, int pos, int num){
	node *tmp, *p;
	int i;
	/* handle errors on position */	
	if(pos < 0 || pos > l->len)
		return;	
	/* create a new node */
	tmp = (node *)malloc(sizeof(node));	
	tmp->num = num;
	/* handle first node case separately */
	if(l->head == NULL) {
		tmp->next = NULL; 
		tmp->prev = NULL;
		l->head = l->tail = tmp;
		l->len++;
		return;		
	}
	/* link the new node on the list at appropriate position*/
	p = l->head;
	for(i = 0; i < pos - 1; i++)
		p = p->next;
	if(pos == 0) {
		tmp->next = l->head;
		l->head->prev = tmp;
		l->head = tmp;
		l->head->prev = NULL;
		l->len++;
		return;
	}
	if(pos != l->len) {
		tmp->next = p->next;
		tmp->prev = p;
		p->next->prev = tmp;
		p->next = tmp;
		l->len++;
		return;
	}
	if(pos == l->len) {
		p->next = tmp;
		l->tail = tmp;
		tmp->prev = p;	
		tmp->next = NULL;
		l->len++;
		return;
	}
}
int remov(list *l, int pos){
	int i;
	int num;
	node *p, *tmp;
	/* handle errors on position */	
	if(pos < 0 || pos >= l->len)
		return 0;	
	
	p = l->head;
	for(i = 0; i < pos - 1; i++)
		p = p->next;
	if(l->head == NULL) {
		printf("\nempty");
		return 0;
	}
	if(l->len == 1) {	
		num = p->num;
		l->head = l->tail = p = NULL;
		l->len--;
		return num;
	}
	if(pos == 0) {	
		num = p->num;
		p->next->prev = NULL;
		l->head = p->next;
		free(p);
		l->len--;
		return num;
	}
	if(pos == l->len - 1) {	
		num = p->next->num;
		tmp = p->next;
		p->next = NULL;
		l->tail = p;
		free(tmp);
		l->len--;
		return num;
	}
	
	tmp = p->next;
	p->next = p->next->next;
	tmp->next->prev = p;	
	num = tmp->num;
	free(tmp);
	l->len--;
	return num;
}
void traverse(list *l){
	node *p = l->head;
	int i = 0;
	if(!p) {
		printf("Forwards: %d[ ]\n", l->len);
		return;
	}
	printf("Forwards: %d[ ", l->len);
	do {
		i++;
		printf("%d", p->num);
		if( i == l->len - l->dec)
			printf(".");
		p = p->next;
	} while(p != NULL) ;
	printf("]\n");
}
void append(list *l, int num) {
	insert(l, l->len, num);
}
int length(list *l) {
	return l->len;
}
int show(list *l, int pos) {
	node *p;
	if(pos <0 || pos > l->len)
		return 0;
	p = l->head;
	int i;
	for(i = 0; i < pos; i++)
		p = p->next;
	return p->num;
}

list *getnum(list *p, char *str) {
	int signbit;
	int i = 0;
	int m = 0;
	int flag = 0;
	//printf("i am inside getnum");
	if(str[0] == '-') {
		signbit = MINUS;
		i = 1;
	}
	else if(str[0] == '+') {
		signbit = PLUS;
		i = 1;
	}
	else
		signbit = PLUS;
	int num;
	char ch;
	while((ch = str[i]) != '\0') {
		if(flag == 1) {
			m++;
		}
		if(ch == '.') {
			flag = 1;
		}
		else {
			num = ch - '0';
			append(p, num);
		}
		i++;
	}
	p->dec = m;
	p->sign = signbit;
	return p;
}
int compare(list *l1, list *l2);
list *subnum(list *l1, list *l2);
list *addnum(list *l1, list *l2) {
	list *result;
	result = (list *)malloc(sizeof(list));
	/*Make no. of digits after decimal equal*/
	if(l1->dec > l2->dec) {
		int i;
		for(i = 0; i < (l1->dec - l2->dec); i++) {
			append(l2, 0);
			l2->dec++;
		}
	}
	else if(l2->dec > l1->dec) {
		int i;
		for(i = 0; i < (l2->dec - l1->dec); i++) {
			append(l1, 0);
			l1->dec++;
		}
	}
	
	if(l1->sign != l2->sign) {
		if(l1->sign == -1) {
			l1->sign = 1;
			result = subnum(l1, l2);
		}
		else if(l2->sign == -1) {
			l2->sign = 1;
			result = subnum(l1, l2);
		}
	}
	else if(l1->sign == l2->sign) {
		if(l1->sign == -1)
			result->sign = -1;
		else
			result->sign = 1;
		int num = 0;
		int carry = 0;
		while(l1->len != 0 || l2->len != 0) {
			if(l1->len == 0) {
				num = remov(l2, l2->len - 1) + carry;
				carry = num / 10;
				num = num % 10;
				insert(result, 0, num);
			}
			else if(l2->len == 0) {
				num = remov(l1, l1->len -1) + carry;
				carry = num / 10;
				num = num % 10;
				insert(result, 0, num);
			}
			else {
				num = remov(l1, l1->len - 1) + remov(l2, l2->len - 1) + carry;
				carry = num / 10;
				num = num % 10;
				insert(result, 0 , num);
			}
		}
		result->dec = l1->dec;
		if(carry != 0)
			insert(result, 0, carry);
	}
	return result;
}

list *subnum(list *l1, list *l2) {
	/*Make no of digits after decimal equal*/
	if(l1->dec > l2->dec) {
		int i;
		for(i = 0; i < (l1->dec - l2->dec); i++) {
			append(l2, 0);
			l2->dec++;
		}
	}
	else if(l2->dec > l1->dec) {
		int i;
		for(i = 0; i < (l2->dec - l1->dec); i++) {
			append(l1, 0);
			l1->dec++;
		}
	}
	int num;
	list *result;
	result = (list *)malloc(sizeof(list));
	if(l1->sign != l2->sign) {
		if(l2->sign == -1) {
			l2->sign = 1;
			result = addnum(l1, l2);
			result->sign = 1;
		}
		if(l1->sign == -1) {
			l1->sign = 1;
			result = addnum(l1, l2);
			result->sign = -1;
		}
	}
	else if(l1->sign == l2->sign) {
		if(l1->sign == -1) {
			l1->sign = 1;
			l2->sign = 1;
			result = subnum(l2, l1);
		}
		if(l1->sign == 1) {
			if(compare(l1, l2) >= 0) {
				int diff = 0, b = 0;
				while(l1->len != 0 || l2->len != 0) {
					if(l2->len == 0) {
						num = remov(l1, l1->len - 1);
						insert(result, 0, num);
					}
					else {
						int a = remov(l1, l1->len - 1);
						int c = remov(l2, l2->len - 1);
						if(a >= c) {
							num = a - c;
							insert(result, 0, num);
						}
						else {
							int d = 0;
							while(!(b = remov(l1, l1->len - 1))) {
								d++;
							}
							append(l1, b - 1);
							int i;
							for(i = 0; i < d; i++)
								append(l1, 9);
							num = 10 + a - c;
							insert(result, 0, num);
						}
					}
				}
			}
			else if(compare(l1, l2) < 0) {
				result = subnum(l2, l1);
				result->sign = -1;
			}
		}
	}
	return result;
}   


list *mulnum(list *l1, list *l2) {
	list *result;
	result = (list *)malloc(sizeof(list));
	int tempsign;
	if(l1->sign == l2->sign) {
		tempsign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		tempsign = -1;
		l1->sign = l2->sign = 1;
	}
	int tempdec = l1->dec + l2->dec;
	list *s;
	s = (list *)malloc(sizeof(list));
	insert(s, 0, 1);
	s->dec = 0;
	s->sign = 1;
	insert(result, 0, 0);
	int k = compare(l1, l2);
	if(k >= 0) {
		l2->dec = 0;
		while(compare(l2, s) >= 0) {
			l2 = subnum(l2, s);
			result = addnum(result, l1);
		}
	}
	result->sign = tempsign;
	result->dec = tempdec;
	return result;
}

int compare(list *l1, list *l2) {
	if(l1->sign == 1 && l2->sign == -1)
		return 1;
	if(l2->sign == 1 && l1->sign == -1)
		return -1;
	/*Make no. of digits after decimal equal*/
	if(l1->dec > l2->dec) {
		int i;
		for(i = 0; i < (l1->dec - l2->dec); i++) {
			append(l2, 0);
			l2->dec++;
		}
	}
	else if(l2->dec > l1->dec) {
		int i;
		for(i = 0; i < (l2->dec - l1->dec); i++) {
			append(l1, 0);
			l1->dec++;
		}
	}
	int a = (l1->len - l2->len);
	if(a > 0)
		return 1;
	else if(a < 0)
		return -1;
	else {
		int i;
		for(i = 1; i <= l1->len; i++) {
			if(show(l1, i) > show(l2, i))
				return 1;
			else if(show(l1, i) < show(l2, i))
				return -1;
		}
		return 0;
	}
}

int readline(char *arr, int len) {
	int k = 0;
	int ch;
	while((ch = getchar()) != '\n' && k < len - 1) {
		arr[k] = ch;
		k++;
	}
	arr[k] = '\0';
	return k;
}

int main() {
	
	printf("enter first:");
	char str1[128], str2[128];
	list *l1, *l2, *l3, *l4;
	l1 = (list *)malloc(sizeof(list));
	l2 = (list *)malloc(sizeof(list));
	l3 = (list *)malloc(sizeof(list));
	l4 = (list *)malloc(sizeof(list));
	init(l1);
	init(l2);
	init(l3);
	init(l4);
	readline(str1, 128);
	//printf("\n%s", str1);
	//getnum(&l1, str1);
	
	printf("enter second");
	readline(str2, 128);
	printf("%s", str2);
	l1 = getnum(l1, str1);
	l2 = getnum(l2, str2);
	l3 = addnum(l1, l2);
	//l4 = mulnum(l1, l2);
	traverse(l1);
	traverse(l2);
	//traverse(&l1);printf(" + ");traverse(&l2);
	traverse(l3);
	//traverse(l4);
	return 0;
}
  

