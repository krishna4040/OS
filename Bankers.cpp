#include <iostream>
using namespace std;

int main()
{
	// P0, P1, P2, P3, P4 are the Process names here

	int n, m;
	n = 5; // Number of processes
	m = 3; // Number of resources
	int alloc[5][3] = { { 0, 1, 0 }, // P0 // Allocation Matrix
					{ 2, 0, 0 }, // P1
					{ 3, 0, 2 }, // P2
					{ 2, 1, 1 }, // P3
					{ 0, 0, 2 } }; // P4

	int max[5][3] = { { 7, 5, 3 }, // P0 // MAX Matrix
				{ 3, 2, 2 }, // P1
				{ 9, 0, 2 }, // P2
				{ 2, 2, 2 }, // P3
				{ 4, 3, 3 } }; // P4

	int avail[3] = { 3, 3, 2 }; // Available Resources

	int isProcessFinished[n];
	for (int k = 0; k < n; k++) {
        // For each process mark their finish as false
		isProcessFinished[k] = 0;
	}
	int need[n][m];
	for (int i = 0; i < n; i++) {
        // calculating need for every resource for each process
		for (int j = 0; j < m; j++)
			need[i][j] = max[i][j] - alloc[i][j];
	}

	for (int k = 0; k < n; k++) {
        // Loop over every process
		for (int i = 0; i < n; i++) {
            // Loop over each process that is not finished
			if (!isProcessFinished[i]) {
				int flag = 0;
                // Loop over each resource
				for (int j = 0; j < m; j++) {
					if (need[i][j] > avail[j]){
						flag = 1;
						break;
					}
				}
				if (!flag) {
					for (int y = 0; y < m; y++)
						avail[y] += alloc[i][y];
					isProcessFinished[i] = 1;
				}
			}
		}
	}

	cout << "New value of available resources:" << endl;
	for (int i = 0; i < m; i++)
		cout << avail[i] << " ";
	cout << endl;

	return 0;
}