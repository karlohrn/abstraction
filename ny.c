void swap_ref(int *p, int *s){
  int tmp = *p;
  *p = *s;
  *s = tmp;
}

int *swap_value(int a, int b, int *arr){
  arr[0] = b;
  arr[1] = a;
  return arr;
}

main(){
  int arr[2];
  int a = 5, b = 10;
  swap_value(a, b);
  printf("a=%d; b=%d\n", a, b);
}
