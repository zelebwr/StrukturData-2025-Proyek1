# StrukturData-2025-Proyek1
---
#### Kelompok 4

| No. | Nama                                    | NRP         | Struktur Data |
|-----|-----------------------------------------|-------------|----------------|
| 1   | Salomo                                  | 5027221063  | Stack          |
| 2   | Revalina Erica Permatasari              | 5027241007  | Queue          |
| 3   | Jonathan Zelig Sutopo                   | 5027241047  | Hash Table     |
| 4   | Dina Rahmadani                          | 5027241065  | Array          |
| 5   | Ahmad Rafi Fadhillah Dwiputra           | 5027241068  | Map            |
| 6   | Mutiara Diva Jaladitha                  | 5027241083  | Linked List    |

---
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

### Bagaimana cara kerja struktur data jika dikaitkan dengan Skyline problem?

Di code ini menggunakan vector (std::vector dari STL) sebagai pengganti array statis.
Fungsi vector:
Menyimpan daftar produk yang di-load dari CSV
Menyimpan hasil produk skyline
Tanpa batasan ukuran tetap seperti array, karena vector bisa growable (dinamis)

Vector di sini berperan sebagai:
Tempat penyimpanan dinamis untuk produk (vector<Product> products)
Tempat hasil skyline (vector<Product> skyline)


Kenapa tidak menggunakan full Array (Array Statis)?

Ukuran harus ditentukan di awal
Di array statis:
Ukurannya harus ditentukan fix waktu compile (MAX_PRODUCTS misalnya)
Overflow, kalau ternyata data di CSV lebih dari itu
Wasting Memory, kalau data jauh lebih sedikit 

Sedangkan vector bisa menyesuaikan:
Tambah elemen sesuka hati dengan push_back()
Tidak perlu menentukan berapa banyak data yang bakal dimuat

Tidak scalable
Jika ada perubahan data dari 1.000 menjadi 500 
Array statis harus di ubah manual ukuran MAX_PRODUCTS
Rawan lupa atau salah hitung

Dengan vector:
Ukuran bisa otomatis menyesuaikan saat push_back() dipanggil
Lebih aman dan maintainable

### Performa

Kompleksitas waktu:
Skyline calculation tetap O(n²)
      Karena prosesnya masih:
Loop outer for (const auto &p : products)
Loop inner for (const auto &q : products)
Cek dominates(q, p)

Kompleksitas memori:
O(n) karena vector menyimpan data produk + hasil skyline
     Bedanya:
vector ukurannya dinamis
Lebih efisien memory kalau jumlah produk bervariasi

Waktu akses elemen vector juga O(1) seperti array.
Tapi karena ada dynamic resizing saat push_back(), ada overhead sedikit. (meskipun amortized O(1)).

### Mengapa struktur data cepat / lambat dalam memproses skyline query

Jumlah Perbandingan
Skyline query itu by nature O(n²) kalau brute force, karena:
Setiap data dibandingkan dengan semua data lain.
Artinya:
Kalau data 1000 → 1000×1000 = 1.000.000 perbandingan.
Kalau data 10.000 → 100 juta perbandingan.
Jadi semakin banyak data → prosesnya kuadrat makin berat.

Efisiensi Struktur Data
Vector:
Dinamis, fleksibel.
Tapi kalau tetap brute force loop bersarang, tetap O(n²).
Vector cepat buat akses elemen O(1) tapi looping tetap berat kalau datanya banyak.
Array:
Akses juga O(1).
Tapi harus hati-hati ukuran, tidak bisa fleksibel.
Proses brute force-nya sama beratnya.

---
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

---
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

---

Cara kerjanya seperti ini:
Setelah semua titik di-sort berdasarkan harga naik dan rating turun, kita iterasi satu per satu.
Untuk setiap titik baru p, kita cek elemen puncak stack:
- Jika p mendominasi elemen di puncak stack, kita pop karena artinya elemen lama itu bukan skyline lagi.
- Jika p didominasi, kita skip.
- Jika tidak saling mendominasi, kita push(p) ke dalam stack.
Akhirnya, stack berisi titik-titik skyline dalam urutan menaik sesuai harga.

Performa:
Performa struktur stack dalam skyline query cukup efisien:
Waktu sort: O(n log n) (karena pakai std::sort)
Waktu skyline dengan stack: Amortized O(n)

Artinya, setiap titik hanya bisa masuk dan keluar stack maksimal satu kali. Tidak ada perulangan bersarang seperti di brute-force O(n²). Ini menjadikan total proses lebih cepat.

Mengapa Struktur data tersebut cepat / lambat memproses Skyline Query?
Kenapa cepat:
- Stack berbasis linked-list memungkinkan kita untuk melakukan push, pop, dan peek dalam O(1) waktu.
- Setelah data di-sort, kita hanya perlu satu kali loop melalui semua titik.
- Karena pendekatannya greedy, stack hanya menyimpan titik-titik yang memang belum terdominasi, ini menghindari perbandingan ganda seperti di nested loop.

Tapi ada kekurangan juga:
- Struktur stack tidak cocok untuk lebih dari 2 atribut. Kalau kita ingin skyline dengan 3 atau 4 dimensi (misalnya harga, rating, kualitas, dan garansi), pendekatan ini tidak langsung bisa dipakai.
- Karena menggunakan new/delete untuk tiap node, stack berbasis linked-list sedikit lebih berat daripada array biasa dalam hal alokasi memori dan efisiensi cache.

## Queue
### 1. Hasil Performa
<img width="436" alt="image" src="https://github.com/user-attachments/assets/86674a02-bcfa-4304-8710-0177c8e9a3c2" />

### 2. Analisis Hasil Performa
| **Fungsi**               | **Best Case**      | **Average Case**   | **Worst Case**      | **Penjelasan**                                                    |
|--------------------------|--------------------|--------------------|---------------------|-------------------------------------------------------------------|
| `isNumber()`             | O(L)               | O(L)               | O(L)                | Memeriksa tiap karakter dalam string untuk memastikan apakah string tersebut berisi angka (L = panjang string). |
| `dominates()`            | O(1)               | O(1)               | O(1)                | Membandingkan harga dan rating dua produk secara langsung.        |
| **Data Retrieval Loop**  | O(n)               | O(n)               | O(n)                | Membaca `n` baris dari file CSV dan memasukkan produk ke dalam antrian (`queue`). |
| **Skyline Calculation**  | O(n)               | O(n²)              | O(n²)               | **Best**: Banyak produk tereliminasi awal → O(n). <br> **Average**: Skyline tumbuh lebih banyak, tetapi tidak sepenuhnya bertahan → O(n²). <br> **Worst**: Semua produk bertahan → O(n²). |
| **Print Output**         | O(k)               | O(k)               | O(k)                | Menampilkan `k` produk dari skyline.                             |
| **Total Program**        | O(n)               | O(n²)              | O(n²)               | Gabungan: O(n) I/O + O(n²) skyline + O(k) post-process. |
- `n`: jumlah total produk dalam CSV.
- `k`: jumlah produk dalam hasil skyline (k ≤ n).
- `L`: panjang karakter dari string (untuk fungsi `isNumber()`).

#### Bagaimana cara kerja struktur data jika dikaitkan dengan Skyline problem? 
Skyline problem adalah tentang memilih item (produk) yang tidak didominasi oleh item lain dalam satu set data. Dalam hal ini, item dideskripsikan dengan dua atribut utama, yaitu price dan rating.
Produk A mendominasi produk B jika:
- Harga A lebih murah atau sama dengan B
- Rating A lebih tinggi atau sama dengan B
- Dan setidaknya satu dari kondisi tersebut lebih baik secara ketat

Struktur data queue digunakan sebagai tempat penampungan sementara seluruh data produk yang diambil dari file CSV. Setiap baris data (produk) yang valid akan dimasukkan ke dalam queue, lalu diproses satu per satu untuk menentukan apakah produk tersebut masuk ke dalam skyline set atau tidak.

Kenapa Cocok untuk Skyline?
- Queue menjamin urutan >> Produk diproses sesuai urutan muncul di file CSV.
- Efisien untuk satu arah >> Tidak butuh pencarian acak atau pengulangan data.
- Minim overhead >> Queue tidak membutuhkan banyak manajemen memori atau indexing.

#### Mengapa struktur data tsb cepat / lambat dalam memproses skyline query?
Cepat Saat
- Data input tidak terlalu besar (misalnya ≤ 10.000 produk).
- Produk-produk tidak saling mendominasi banyak >> skyline-nya kecil.
- Operasi dominasi (dominates(...)) cukup ringan karena hanya membandingkan 2 atribut.

Lambat Saat
- Ukuran input sangat besar (100K+) >> O(n²) dalam kasus terburuk.
- Banyak produk yang hampir tidak terdominasi >> skyline membengkak >> perbandingan antar banyak elemen jadi berat.

#### Kelebihan Queue
- Menambah data (`push`) dan mengambil data (`pop`) sangat cepat.  
- Data diproses sesuai urutan datang (First-In, First-Out), jadi mudah dipahami.  
- Pakai `std::queue` langsung bisa, tanpa harus ngatur pointer atau memori manual.  
- Akses memori cukup berurutan, membantu kinerja.  
- Struktur ringan, tidak ada penyeimbangan atau overhead tambahan.
#### Kelebihan Vector
- Akses elemen cepat (O(1) untuk indeks langsung).
- Iterasi efisien untuk jumlah data yang tidak terlalu besar.
- Sangat fleksibel untuk modifikasi seperti insert/erase di akhir.

#### Kelemahan Queue
- Hanya bisa ambil data di depan atau belakang, tidak bisa langsung mengakses elemen di tengah.  
- Untuk melihat semua data, harus terus mengeluarkan (`pop`), artinya data asli akan hilang.  
- Kalau butuh cari data tertentu, harus cek satu per satu secara berurutan.  
- Kurang pas untuk operasi yang membutuhkan akses acak atau query kompleks.
ain linear scan via pop.
#### Kelemahan Vector
Vector tidak efisien saat banyak insert/erase di tengah karena menyebabkan shift elemen — hal ini terjadi dalam skyline.swap(tmp) saat banyak produk harus dihapus.

#### Kenapa Queue Cocok untuk Masalah Skyline?
1. **Urutan Terjaga (FIFO)**
   
Queue memproses data dalam urutan yang sama seperti di file CSV, sehingga tidak ada data yang di-skip atau diulang. Hal ini penting untuk memastikan semua produk dinilai secara adil dalam urutan yang konsisten.

2. **Proses Satu Arah**

 Karena skyline query hanya memerlukan satu kali pemrosesan untuk setiap produk (tidak perlu backtracking atau traversal bolak-balik), maka queue sangat cocok karena hanya menyediakan akses dari depan ke belakang.
 
3. **Efisiensi Memori dan Waktu**

Queue tidak perlu struktur pencarian atau indexing tambahan. Operasi .push(), .front(), dan .pop() semua berjalan dalam waktu konstan (O(1)), yang membuatnya efisien untuk pemrosesan data berukuran besar.

4. **Kesederhanaan Implementasi**

Dengan queue, alur logika lebih mudah dipahami dan tidak perlu manajemen memori yang kompleks seperti pada linked list atau struktur data lainnya.

### 3. Screenshot Input Program 
![Screenshot 2025-04-23 191550](https://github.com/user-attachments/assets/bae5186c-60f3-4e0c-9629-d6bf30889bd4)

### 4. Screenshot Output Program 
<img width="436" alt="image" src="https://github.com/user-attachments/assets/de152151-1f3e-4a7a-acc0-cb8b4ac62022" />

---
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

---
## Map
### 1. Hasil Performa
![image](https://github.com/user-attachments/assets/ae2e673b-b631-4d9f-8776-434aa9c0e807)

### 2. Analisis Hasil Performa

Analisis berikut merinci tahapan-tahapan utama dalam proses skyline query, termasuk struktur data yang digunakan dan kompleksitas waktu dan ruang (Big-O):

| Tahapan                        | Deskripsi                                                                | Struktur Data                         | Time Complexity | Space Complexity          |
|-------------------------------|--------------------------------------------------------------------------|----------------------------------------|------------------|----------------------------|
| 1. Membaca CSV (`readCSV`)    | Membaca dan parsing file, menyimpan ke vector produk                        | `std::vector<Product>`       | O(n)             | O(n)                       |
| 2. Mengelompokkan by Harga             | Memasukkan produk ke `map` berdasarkan harga                                       | `std::map<double, std::vector<Product>>`                 | O(n log n)             | O(n)                       |
| 3. Skyline Filtering     | Linear scan dari harga termurah → memilih rating tertinggi sejauh ini                       | `std::map<std::string, Product>`                 | `O(n log k)`       | `O(k) (hasil skyline) `                         |
| 4. Copy hasil ke vector          | Menyalin hasil skyline ke vector      | `std::map<std::string, Product>`       | `O(k)`             | `O(k)`       |
| 5. Cari Produk Terbaik   | Iterasi hasil skyline untuk cari rating tertinggi & harga termurah       | `std::vector<Product>`               | `O(k)`             | `O(k)`                          |
| 6. Sortir Hasil Skyline         | Mengurutkan hasil skyline berdasarkan rating (desc) dan harga (asc)      | `std::vector<Product>`                    | `O(k log k)`       | `O(k)`                       |
| 7. Output + Cetak Statistik     | Menampilkan hasil, performa, dan memory usage      |  `std::cout / variabel biasa` |  `O(k)`    | -     |

**Total (Dominasi Kompleksitas Waktu)**

- **Time Complexity Total**: `O(n log n)`
- **Space Complexity Total**: `O(n)`

---

**Keterangan:**

- `n` = jumlah total produk dalam dataset
- `k` = jumlah hasil dari skyline query (biasanya jauh lebih kecil dari `n`)

### 3. Screenshot Input Program 
![image](https://github.com/user-attachments/assets/72296618-021c-4989-95f3-4c1ab90cd2e1)
### 4. Screenshot Output Program 
![image](https://github.com/user-attachments/assets/7b69f18e-0b70-45f3-93f6-1b5ce6ca65df)

---
## Perbandingan Waktu Komputasi Masing-masing Struktur Data
|Functional Process|Array|Linked List|Stack|Queue|Hash Table|Map|
|---|---|---|---|---|---|---|
|Data Retrieval|`O(n)`|`O(n)`|`O(n)`|`O(n)`|`O(n)`|`O(n)`|
|Skyline Calculation|`O(n²)`|`O(n²)`|`O(n)`|`O(n²)`|`O(n²)`|`O(n log n)`|

## Kesimpulan

Jadi dari hasil program-program kami, struktur yang programnya tercepat adalah: 
1. Stack
2. Linked List 
3. Map 

Hal ini bisa terjadi disebabkan beberapa faktor, yaitu: 
1. Performa perangkat dari masing-masing penguji program
2. Besar Dataset
3. Efisiensi program yang telah dibuat oleh para Developer program



Secara teoritis, dengan dataset yang terkontrol dan operasi program yang sudah diefisienkan, hasil struktur data yang paling optimal seharusnya merupakan Array dan Map disebabkan kemampuan struktur data mereka yang melakukan proses akses data yang cepat, dengan kondisi tertentu yang harus ditemui. Tetapi untuk sekarang ini hasil kami berbeda dengan hasil tersebut. Hal ini dapat terjadi karena berbagai faktor seperti: 

### 1. Kontrol Efisiensi yang berbeda-beda tiap program
Dengan perbedaan akan kemampuan dan pemahaman tiap developer program, maka hasil dari efisiensi program sendiri berbeda-beda dan hasil dari ini dapat menyebabkan efisiensi programn juga beragam dengan standar yang berbeda-beda. Dengan tanpa adanya kontrol kualitas/efisiensi program satu dengan program yang lainnya dapat menghasilkan hasil performa yang berbeda dan, mungkin, kurang akurat. 

### 2. Implementasi Algoritma dan Library yang berbeda
Ragam algoritma dan library yang ada dan sudah disediakan oleh C++ sendiri terdapat banyak dan berbeda-beda kegunaannya. Ada beberapa dari kami sendiri yang menggunakan library yang terkhususkan untuk suatu struktur data dan ada juga yang tanpa menggunakan library terkhususkan jika tidak harus. Ada juga yang menggunakan logika pemrograman/algoritma yang berbeda dengan satu sama lain, menyebabkan program satu sama lain memiliki perbedaan dalam efisiensi. Dengan menambahkan function `sort()` ada kemungkinan terjadi suatu proses di luar dugaan yang membuat efisiensi program meningkat. Ada juga kasus di mana suatu implementasi algoritma lain yang mungkin dapat menurunkan efisiensi program. 

### 3. Fokus Manfaat Struktur Data yang bebeda
Tiap struktur data sendiri memiliki fokus manfaat tersendiri. Mereka memiliki situasi yang dikhususkan untuk mereka sendiri agar dapat menyelesaikan suatu permasalahan dalam situasi tersebut dengan cara yang paling mudah dan paling efisien. Dengan begitu dengan fokus yang berbeda-beda, pastinya performa tiap struktur data dalam operasi skyline query sendiri dapat berbeda-beda. Tiap struktur data memiliki kegunaan masing-masing, dan memiliki dataset mereka sendiri dimana mereka mungkin lebih handal dibandingkan dengan yang lainnya. Seperti Array lebih efisien untuk mengolah dataset yang lebih kecil (karena memori yang diambil map berlebihan) dibandingkan dengan Map ketika melakukan skyline query, dan juga sebaliknya map lebih efisien dibandingkan array di saat melakukan skyline query dengan dataset yang lebih besar.

### 4. Alur dan Jumlah Operasi yang berbeda
Alur dan Jumlah Operasi yang berbeda merupakan salah satu faktor utama di saat membandingkan performa dari suatu program dengan program yang lainnya. Ketika alur dari program A dengan program B berbeda, terdapat sebuah proses redundansi sendiri-sendiri yang dapat mengurangi performa dari program. Seperti perbedaan dari alur, jumlah operasi yang dimiliki program sendiri juga berpengaruh pada performa dari program. Kembali lagi kepada efisiensi dari program, apabila program satu dengan program yang lainnya memiliki satu operasi yang sama tetapi satu dilakukan dengan cara yang berbeda, hal ini berpengaruh pada operasi. 
---

Mungkin, selain dari faktor-faktor di atas, mungkin dapat dilihat lebih detail melalui time complexity yang sudah dijelaskan sebelumnya pada penjelasana analisis data di atas. Apabila dilihat dari time complexity stack, linked list, dan map, mereka memiliki time complexity yang lebih baik dibandingkan yang lain. Dengan begitu performa mereka juga selayaknya lebih tinggi dibandingkan dengan performa program yang lainnya. 

Alhasil, dengan pertimbangan semua faktor-faktor di atas dan hasil analisis kami semua untuk tiap struktur data, maka untuk struktur data paling efisen adalah: 
1. Stack 
2. Linked List
3. Map
4. `<other data structure>`

