typedef struct {
    int _int;
    char _char;
    double _double;
} _Fields;

typedef struct {
    int field_int;
    char field_char;
    _Fields _feld;
    double field_double;
} Fields;
int azaza(){
    int bye = 999;
    bye = 0;
    Fields field;
    return 0;
}


int ololo(){
	int hello = 0;
	hello = 999;
	azaza();
	return 0;
	
}

int main(void){
        int x = 0;
		int* x_ptr;
        double l;
		x_ptr = &x;
		ololo();
		int* lol[2][5];
		double doubl[5];
        double* d = &l;
        char** carray = new char*[2];
        for(int i = 0; i < 2; i++)
            carray[i] = new char[3];

		return 0;
}
