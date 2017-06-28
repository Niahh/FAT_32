typedef struct point {int x; int y;}point ;
typedef struct pod pod;
struct pod{
	point* position;
	point* vitesse;
	float angle;
	int next_cp_id;
}


void destroy_pod(pod* pod){
	free(pod->position);
	free(pod->vitesse);
	free(pod);
}
point* getPoint (int x, int y) {
	int pointx = x;
	int pointy = y;
	point* po1;
	po1 = malloc(sizeof(point));
	po1->x = pointx;
	po1->y = pointy;
	return po1 ;  
}

int point_equals(point* a, point* b){
	return a->x == b->x && a->y == b->y;
}
int find_in_array(point* to_find, point** array){
	point inter;
	inter.x = 0;
	inter.y = 0;
	point* pt = &inter;
	int index;
	while(!point_equals(to_find,pt)){
		pt = array[index];
		index++;
	}
	return index;
}

int main(){
	point** tableau;
	tableau  = malloc(5*sizeof(point*));
	int current_cp = 0;
	int completed=0;
	point* last_cp = getPoint(0,0);
	while (1) {
		scanf("%d",&nb_cp);
		int next_cp_x;
		int next_cp_y;
		scanf("%d %d",&x,&y);
		point* next_cp = getPoint(x,y);
		if (point_equals(next_cp,*tableau)){
			completed = 1;	
		}
		if (!completed){
			play_bad();
			if (!point_equals(next_cp,last_cp)){
				tableau[current_cp] = next_cp;
				current_cp++;	
			}
		}else {
			int next_cp_id = find_in_array(next_cp,tableau);
		}

		free(last_cp);
		last_cp = next_cp;
	}
}
