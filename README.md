# StrukturData-2025-Proyek1

#### Kelompok 4
1. Salomo (5027221063) - Stack
2. Revalina Erica Permatasari (5027241007) - Queue
3. Jonathan Zelig Sutopo (5027241047) - Hash Table
4. Dina Rahmadani (5027241065) - Array
5. Ahmad Rafi Fadhillah Dwiputra (5027241068) - Map
6. Mutiara Diva Jaladitha (5027241083) - Linked List

## Array
### 1. Hasil Performa
### 2. Analisis Hasil Performa
### 3. Screenshot Input Program 
![Screenshot 2025-04-23 191550](https://github.com/user-attachments/assets/bae5186c-60f3-4e0c-9629-d6bf30889bd4) 
### 4. Screenshot Output Program 
<img width="371" alt="image" src="https://github.com/user-attachments/assets/b44b5ee6-8200-43dd-ba5c-0e31d9387176" />

## Linked List
### 1. Hasil Performa
![Screenshot 2025-04-23 210731](https://github.com/user-attachments/assets/e780c871-588b-4199-9fca-83f3b97a876e)
### 2. Analisis Hasil Performa
### 3. Screenshot Input Program 
![Screenshot 2025-04-23 210947](https://github.com/user-attachments/assets/8e0e9569-8745-4c1a-9734-cb634ecc430b)
### 4. Screenshot Output Program 
![Screenshot 2025-04-23 210807](https://github.com/user-attachments/assets/a5f7ff3b-6a12-42a6-8e14-e65f307ad56a)

## Stack
### 1. Hasil Performa
![Image](https://github.com/user-attachments/assets/ea7e2a33-1022-467d-a9e2-bb6812a3e926)
### 2. Analisis Hasil Performa
### 3. Screenshot Input Program 
![Image](https://github.com/user-attachments/assets/83293bf8-10c1-4a3d-aaba-f028dbcadaa3)
### 4. Screenshot Output Program 
![Image](https://github.com/user-attachments/assets/9c64e70e-342d-466c-bfcd-18162644971a)

## Queue
### 1. Hasil Performa
### 2. Analisis Hasil Performa
### 3. Screenshot Input Program 
![Screenshot 2025-04-23 191550](https://github.com/user-attachments/assets/bae5186c-60f3-4e0c-9629-d6bf30889bd4)

### 4. Screenshot Output Program 
![Screenshot 2025-04-23 185714](https://github.com/user-attachments/assets/34bbcd19-c471-4d6e-be05-1682680e8129)

## Hash table
### 1. Hasil Performa
![image](https://github.com/user-attachments/assets/3680192e-6af1-41af-a554-5eab0dd14173)

### 2. Analisis Hasil Performa
Apabila dilihat dari keseluruhan program hashTable, Time Complexity dari program adalah sebagai berikut: 

| Function | Best Case | Worst Case | Average Case | Explanation |
| `hashFunction` | O(L) | O(L) | O(L) | `L` is defined as the length of the string that is being hashed upon. |
| `add` | O(1) | O(n) | O(1) | While in adding a Node in a Hash Table can be O(1), due to the need of *Collision Handling* the worst case maybe O(n) due to the traversal process being done in buckets. Although, the best case scenario, where there are no collisions happening might make that into O(1). |
| `contains` | O(1) | O(n) | O(1) | Alike with the `add()` function, this function also has the same scenarios. But, where the checker founds out that there is no hash index in the hash table. |
| `remove` | O(1) | O(n) | O(1) | Alike with the `add()` function this function also has the same scenarios. But this can be cut short when the checker (still through traversing using `remove()` function) founds there is no such value in the Hash Set |
| `printRatingSkyline` | O(n) | O(n) | O(n) | Due to the need of traversing using to check the Maximum Rating and Print Out (collect the product with such price), every case is O(n), where there happens two traversals. |
| `printPriceSkyline` | O(n) | O(n) | O(n) | Alike `printRatingSkyline()` function, it also needs to do traversing twice but checks for Minimum Price instead, with all cases as O(n). |
| `printTopSkyline` | O($n^2$) | O($n^2$) | O($n^2$) | Due to the need to check all of the items to see if the product is being dominated or dominating, it needs a `nested loop` process. So, all of the comparison will take O($n^2$) Time Complexity to be done. |


### 3. Screenshot Input Program 
![image](https://github.com/user-attachments/assets/0988e22c-28e0-4cd6-958b-561388fd5315)

### 4. Screenshot Output Program 
![image](https://github.com/user-attachments/assets/f7600e02-4821-4328-b012-1e6e5ede4c7a)


## Map
### 1. Hasil Performa
![image](https://github.com/user-attachments/assets/14cae447-c8aa-418e-94e8-7736c7ce8c80)
### 2. Analisis Hasil Performa
#### Analisis Performa *Skyline Query* dengan *Map*

##### Karakteristik:
- Pembacaan data *.csv* menggunakan konsep operasi **insert, erase, find, access** dalam **notasi O(log n)**
-   Implementasi analisis *skyline query* terhadap data berbasis **Red-Black Tree** (balanced binary search tree).

##### Analisis logika *Skyline Query* (`skylineQueryMap`) dengan *Map*
-   **Struktur**: Hanya menggunakan `std::map`
    
-   **Operasi**:
    
    -   Nested loop antar semua entri → membandingkan keseluruhan entri produk `p1` dengan semua `p2`. → secara *brute-force*.
        
    -   Setiap produk dicek apakah **didominasi** oleh produk lain (berdasarkan harga dan rating).
        
-   **Kompleksitas**:
    
    -   Outer loop (`n` produk) × Inner loop (`n` produk) → **O(n²)** 

### 3. Screenshot Input Program
![image](https://github.com/user-attachments/assets/019a1173-ac22-435a-be29-eb8b7536f4f9)
### 4. Screenshot Output Program
![image](https://github.com/user-attachments/assets/baed9188-92da-497d-bc1e-aa623be8744a)


## Kesimpulan

3. Analisis hasil dari performa struktur data. Kaitkan dengan kompleksitas BigO Notation. 
a. Manakah struktur data yang paling efisien dalam memproses skyline query?  
b. Mengapa?
