# StrukturData-2025-Proyek1

#### Kelompok 4

| No. | Nama                                    | NRP         | Struktur Data |
|-----|-----------------------------------------|-------------|----------------|
| 1   | Salomo                                  | 5027221063  | Stack          |
| 2   | Revalina Erica Permatasari              | 5027241007  | Queue          |
| 3   | Jonathan Zelig Sutopo                   | 5027241047  | Hash Table     |
| 4   | Dina Rahmadani                          | 5027241065  | Array          |
| 5   | Ahmad Rafi Fadhillah Dwiputra           | 5027241068  | Map            |
| 6   | Mutiara Diva Jaladitha                  | 5027241083  | Linked List    |


## Array
### 1. Hasil Performa
![output array crop](https://github.com/user-attachments/assets/1f8de5b7-684c-48b6-8563-5d839332b798)
### 2. Analisis Hasil Performa
| Function | Best Case | Worst Case | Average Case |
|---|---|---|---|
| Data Retrieval | O(n) | O(n) | O(n) |
| Dominance Check | O(1) | O(1) | O(1) |
| Skyline Computation | O($n^2$) | O($n^2$) | O($n^2$) |

Dapat dilihat dengan menggunakan struktur data array bahwa penggunaan dapat dibilang cukup sesuai untuk implementasi Skyline Query karena kecepatan data akses yang cepat dan penggunaan memory yang tidak terlalu banyak. Tetapi hal ini bergantung pada jumlah dari dataset. Jika dengan menggunakan dataset yang berjumlah sedikit, array merupakan pilihan data struktur terbaik. Tetapi jika diperuntukkan dataset yang besar, maka array akan menjadi lebih tidak efisien. Hal ini dikarenakan operasi array lebih sederhana dan menggunakan metode yang lebih *straightforward* dan melakukan traversal pada tiap item untuk mendapatkan skyline querynya.

### 3. Screenshot Input Program 
![Screenshot 2025-04-23 191550](https://github.com/user-attachments/assets/bae5186c-60f3-4e0c-9629-d6bf30889bd4) 
### 4. Screenshot Output Program 
![WhatsApp Image 2025-04-23 at 21 56 48_ff289abc](https://github.com/user-attachments/assets/59f6f5fa-ae2a-4f94-829c-0c62b8448dc0)

## Linked List
### 1. Hasil Performa
![Screenshot 2025-04-23 210731](https://github.com/user-attachments/assets/e780c871-588b-4199-9fca-83f3b97a876e)
### 2. Analisis Hasil Performa
#### a. Apakah linked list efisien dalam memproses Skyline Query?
Tidak terlalu efisien untuk kasus data besar, tapi masih layak digunakan untuk data kecil–menengah (seperti 1000 baris).

#### b. Mengapa? (Penjelasan dan Analisis Big-O)
Struktur Linked List
- Tidak mendukung akses acak langsung (seperti array atau vector).
- Untuk mencari elemen tertentu, traversal harus dilakukan dari awal ke akhir.
- Operasi seperti pengecekan dominasi antar elemen membutuhkan loop bersarang.

#### Kompleksitas Algoritma Skyline Query dengan Linked List
```
for (s in data) {
    for (sk in skyline) {
        if (dominates(sk, s)) ...
    }
    // menambahkan ke skyline baru, jika tidak didominasi
}
```
- Outer loop: O(n) → n = jumlah elemen
- Inner loop: Dalam kasus terburuk, skyline bisa berisi hampir seluruh elemen → O(n)
- Maka total kompleksitas: O(n²)

Contoh:
Untuk n = 1000, maka estimasi perbandingan bisa mencapai 1 juta operasi.
Namun, karena kondisi dominasi memfilter elemen, inner loop sering lebih pendek dari n → kompleksitas rata-rata lebih rendah, tapi tetap quadratic worst-case.

#### Efisiensi Operasi di Linked List
| Operasi             | Kompleksitas             | Keterangan                      |
|---------------------|--------------------------|---------------------------------|
| Traversal           | O(n)                     | Perlu iterasi node per node     |
| Penambahan di akhir | O(n) tanpa tail, O(1) dengan tail |                               |
| Pencarian / dominasi| O(n)                     | Tidak bisa akses acak           |
| Penghapusan semua   | O(n)                     | Satu loop sudah cukup           |

#### Kelemahan Linked List untuk Skyline
- Traversal lambat – butuh waktu untuk menjelajahi semua node.
- Tidak cache-friendly – pointer menyebar di memori.
- Tidak cocok untuk data besar – karena `O(n²)` bisa jadi sangat lambat
#### Kelebihan (untuk dataset kecil–menengah)
- Mudah diimplementasikan.
- Penggunaan memori efisien (tergantung ukuran elemen).
- Cocok untuk eksperimen awal, tugas kecil, atau dataset terbatas (< 10.000).
### 3. Screenshot Input Program 
![Screenshot 2025-04-23 210947](https://github.com/user-attachments/assets/8e0e9569-8745-4c1a-9734-cb634ecc430b)
### 4. Screenshot Output Program 
![Screenshot 2025-04-23 210807](https://github.com/user-attachments/assets/a5f7ff3b-6a12-42a6-8e14-e65f307ad56a)

## Stack
### 1. Hasil Performa
![Image](https://github.com/user-attachments/assets/ea7e2a33-1022-467d-a9e2-bb6812a3e926)
### 2. Analisis Hasil Performa

| Langkah                  | Deskripsi Singkat                         | Time Complexity | Space Complexity |
|--------------------------|---------------------------------------------|-----------------|------------------|
| **1. Load Data**         | Buka & parse CSV (n baris)                  | O(n)            | O(n)             |
| **2. Sorting**           | `std::sort` by price ↑, tie → rating ↓      | O(n log n)      | O(log n)         |
| **3. Skyline Calc.**     | One-pass stack-based skyline                | O(n)            | O(n)             |
| **4. Output Results**    | Cetak m titik skyline                       | O(m)            | O(m)             |
| **5. Memory Measure**    | Panggilan API OS untuk working set size     | O(1)            | O(1)             |
| **Total**                | Dominasi oleh sorting + skyline pass        | O(n log n)      | O(n)             |

- **n** = jumlah entri (mis. 1000)  
- **m** = jumlah titik skyline (≤ n)  


### 3. Screenshot Input Program 
![Image](https://github.com/user-attachments/assets/83293bf8-10c1-4a3d-aaba-f028dbcadaa3)
### 4. Screenshot Output Program 
![Image](https://github.com/user-attachments/assets/9c64e70e-342d-466c-bfcd-18162644971a)

## Queue
### 1. Hasil Performa
![Screenshot 2025-04-23 235211](https://github.com/user-attachments/assets/cc94feda-8a89-4119-a307-809d717f230f)

### 2. Analisis Hasil Performa
| **Fungsi**               | **Best Case**      | **Average Case**   | **Worst Case**      | **Penjelasan**                                                    |
|--------------------------|--------------------|--------------------|---------------------|-------------------------------------------------------------------|
| `isNumber()`             | O(L)               | O(L)               | O(L)                | Memeriksa tiap karakter dalam string untuk memastikan apakah string tersebut berisi angka (L = panjang string). |
| `dominates()`            | O(1)               | O(1)               | O(1)                | Membandingkan harga dan rating dua produk secara langsung.        |
| **Data Retrieval Loop**  | O(n)               | O(n)               | O(n)                | Membaca `n` baris dari file CSV dan memasukkan produk ke dalam antrian (`queue`). |
| **Skyline Calculation**  | O(n)               | O(n log n)         | O(n²)               | **Best**: Banyak produk tereliminasi awal → O(n). <br> **Average**: Skyline tumbuh sekitar logaritmik → O(n log n). <br> **Worst**: Semua produk bertahan → O(n²). |
| **Highest/Lowest Check** | O(k)               | O(k)               | O(k)                | Pencarian linear untuk menemukan produk dengan rating tertinggi dan harga terendah, di mana `k` adalah ukuran skyline. |
| **Print Output**         | O(k)               | O(k)               | O(k)                | Menampilkan `k` produk dari skyline.                             |
| **Total Program**        | O(n)               | O(n log n)         | O(n²)               | Akumulasi: O(n) I/O + O(n log n) skyline + O(k) post-process. |

#### Kelebihan Queue
- Menambah data (`push`) dan mengambil data (`pop`) sangat cepat.  
- Data diproses sesuai urutan datang (First-In, First-Out), jadi mudah dipahami.  
- Pakai `std::queue` langsung bisa, tanpa harus ngatur pointer atau memori manual.  
- Akses memori cukup berurutan, membantu kinerja.  
- Struktur ringan, tidak ada penyeimbangan atau overhead tambahan.

#### Kelemahan Queue
- Hanya bisa ambil data di depan atau belakang, tidak bisa langsung mengakses elemen di tengah.  
- Untuk melihat semua data, harus terus mengeluarkan (`pop`), artinya data asli akan hilang.  
- Kalau butuh cari data tertentu, harus cek satu per satu secara berurutan.  
- Kurang pas untuk operasi yang membutuhkan akses acak atau query kompleks.
ain linear scan via pop.

### 3. Screenshot Input Program 
![Screenshot 2025-04-23 191550](https://github.com/user-attachments/assets/bae5186c-60f3-4e0c-9629-d6bf30889bd4)

### 4. Screenshot Output Program 
![Screenshot 2025-04-23 235211](https://github.com/user-attachments/assets/06f2ec33-8335-423f-a9e5-a27d961ffe01)

## Hash table
### 1. Hasil Performa
![image](https://github.com/user-attachments/assets/3680192e-6af1-41af-a554-5eab0dd14173)

### 2. Analisis Hasil Performa
Apabila dilihat dari keseluruhan program hashTable, Time Complexity dari program adalah sebagai berikut: 

| Function | Best Case | Worst Case | Average Case | Explanation |
|---|---|---|---|---|
| `hashFunction` | O(L) | O(L) | O(L) | `L` is defined as the length of the string that is being hashed upon. |
| `add` | O(1) | O(n) | O(1) | While in adding a Node in a Hash Table can be O(1), due to the need of *Collision Handling* the worst case maybe O(n) due to the traversal process being done in buckets. Although, the best case scenario, where there are no collisions happening might make that into O(1). |
| `contains` | O(1) | O(n) | O(1) | Alike with the `add()` function, this function also has the same scenarios. But, where the checker founds out that there is no hash index in the hash table. |
| `remove` | O(1) | O(n) | O(1) | Alike with the `add()` function this function also has the same scenarios. But this can be cut short when the checker (still through traversing using `remove()` function) founds there is no such value in the Hash Set |
| `printRatingSkyline` | O(n) | O(n) | O(n) | Due to the need of traversing using to check the Maximum Rating and Print Out (collect the product with such price), every case is O(n), where there happens two traversals. |
| `printPriceSkyline` | O(n) | O(n) | O(n) | Alike `printRatingSkyline()` function, it also needs to do traversing twice but checks for Minimum Price instead, with all cases as O(n). |
| `printTopSkyline` | O($n^2$) | O($n^2$) | O($n^2$) | Due to the need to check all of the items to see if the product is being dominated or dominating, it needs a `nested loop` process. So, all of the comparison will take O($n^2$) Time Complexity to be done. |

Kelebihan menggunakan Hash Table: 
1. Operasi akses data yang sangat cepat, karena berdasarkan suatu `key`.
2. Operasi memasukkan, meng**ha**pus, dan pencarian data yang cepat.
3. Ditujukan untuk **alokasi data secara dinamis**. 

Kekurangan menggunakan Hash Table:
1. **Memerlukan** `Collision Handling`, dan hal ini dilakukan melalui proses yang lebih rumit lagi, seperti melibatkan struktur data yang lain.
2. **Tidak mengurutkan data** di dalam struktur data. 
3. Bisa terjadi **penghabisan memori yang berlebihan**.
4. **Tidak cocok** untuk operasi **`real-time`**.

Struktur data Hash Table lebih cocok untuk dataset yang: 
1. **Memiliki `Unique Key`**, sebagai identifiers tersendiri.
2. **Tidak** membutuhkan akses yang **diurutkan**. 
3. **Frekuensi akses data** yang **tinggi**.
4. Bisa untuk dataset yang baik **kecil** maupun **sangat besar**

Untuk implementasi struktur data *Hash Table* sendiri untuk Skyline Query, bukanlah yang terbaik. Penggunaan struktur data ini **bukan ditujukan untuk implementasi Skyline Query**, alhasil operasi yang **tidak efisien**. Untuk spesifiknya, adalah disebabkan Hash Map yang menggunakan `Collision Handling` yang beragam dan membutuhkan `Unique Key` tersendiri, dan tergantung dari metode *Developer*, performa program dapat beragam juga.
git 
### 3. Screenshot Input Program 
![image](https://github.com/user-attachments/assets/0988e22c-28e0-4cd6-958b-561388fd5315)

### 4. Screenshot Output Program 
![image](https://github.com/user-attachments/assets/f7600e02-4821-4328-b012-1e6e5ede4c7a)


## Map
### 1. Hasil Performa
![image](https://github.com/user-attachments/assets/4613daa3-8576-4981-a85c-f554564aaa9c)

### 2. Analisis Hasil Performa
#### Analisis Performa *Skyline Query* dengan *Map*
#### Analisis Performa Skyline Query

Analisis berikut merinci tahapan-tahapan utama dalam proses skyline query, termasuk struktur data yang digunakan dan kompleksitas waktu dan ruang (Big-O):

| Tahapan                        | Deskripsi                                                                | Struktur Data                         | Time Complexity | Space Complexity          |
|-------------------------------|--------------------------------------------------------------------------|----------------------------------------|------------------|----------------------------|
| 1. Membaca CSV (`readCSV`)    | Membaca dan parsing file, menyimpan ke `std::map`                        | `std::map<std::string, Product>`       | O(n)             | O(n)                       |
| 2. Copy ke Vector             | Menyalin produk dari map ke vector                                       | `std::vector<Product>`                 | O(n)             | O(n)                       |
| 3. Sort Berdasarkan Harga     | Mengurutkan produk dengan `std::sort` (harga naik)                       | `std::vector<Product>`                 | O(n log n)       | -                          |
| 4. Skyline Filtering          | Linear scan untuk memilih produk dengan rating tertinggi sejauh ini      | `std::map<std::string, Product>`       | O(n)             | O(k) (hasil skyline)       |
| 5. Pencarian Produk Terbaik   | Iterasi hasil skyline untuk cari rating tertinggi & harga termurah       | `std::map` atau `vector`               | O(k)             | -                          |
| 6. Sort Hasil Skyline         | Mengurutkan hasil skyline berdasarkan rating (desc) dan harga (asc)      | `std::vector<pair>`                    | O(k log k)       | O(k)                       |

#### Total (Dominasi Kompleksitas Waktu)

- **Time Complexity Total**: `O(n log n)`
- **Space Complexity Total**: `O(n)`

---

**Keterangan:**

- `n` = jumlah total produk dalam dataset
- `k` = jumlah hasil dari skyline query (biasanya jauh lebih kecil dari `n`)

## Kesimpulan
a. Manakah struktur data yang paling efisien dalam memproses skyline query?

b. Mengapa?
