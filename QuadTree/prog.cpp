struct quad {
	int x[2], y[2];
	int val, valid;
	quad * c[2][2];
	quad(){ val = 0; }
	quad(int x1, int y1, int x2, int y2) {
		x[0] = x1;
		y[0] = y1;
		x[1] = x2;
		y[1] = y2;
		val = 0;
		valid = true;
	}
	static quad * invalid() {
		quad * q = new quad;
		q->valid = false;
		return q;
	}
};

int mat[1007][1007];

quad * build(int x1, int y1, int x2, int y2) {
	quad * no = new quad(x1, y1, x2, y2);
	if(x1 == x2 and y1 == y2)
		no->val = mat[x1][y1];
	else {
		int mx = (x1 + x2)/2;
		int my = (y1 + y2)/2;
		for(int i = 0; i < 2; ++i) {
			for(int j = 0; j < 2; ++j) {
				if(i and mx + 1 > x2) no->c[i][j] = quad::invalid();
				else if(j and my + 1 > y2) no->c[i][j] = quad::invalid();
				else {
					no->c[i][j] = build(i? mx+1 : x1, j? my+1 : y1, i? x2 : mx, j? y2 : my);
					no->val += no->c[i][j]->val;
				}
			}
		}
	}
	return no;
}

void update(quad * cur, int x, int y, int val) {
	if(cur->valid == false or cur->x[1] < x or cur->x[0] > x or cur->y[1] < y or cur->y[0] > y) return;
	if(cur->x[0] == x and cur->x[1] == x and cur->y[0] == y and cur->y[1] == y) cur->val = val;
	else {
		int ans = 0;
		for(int i = 0; i < 2; ++i) {
			for(int j = 0; j < 2; ++j) {
				update(cur->c[i][j], x, y, val);
				ans += cur->c[i][j]->val;
			}
		}
		cur->val = ans;
	}
}

int query(quad * cur, int x1, int y1, int x2, int y2) {
	if(cur->valid == false or cur->x[1] < x1 or cur->x[0] > x2 or cur->y[1] < y1 or cur->y[0] > y2) return 0;
	if(cur->x[0] >= x1 and cur->x[1] <= x2 and cur->y[0] >= y1 and cur->y[1] <= y2) return cur->val;
	else {
		int ans = 0;
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				ans += query(cur->c[i][j], x1, y1, x2, y2);
		return ans;
	}
}