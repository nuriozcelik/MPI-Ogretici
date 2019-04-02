# NOKTADAN NOKTAYA İLETİŞİM
MPI ilk baştada bahsedildiği gibi işlemler arasında veri alışverişine dayalı bir kütüphanedir. Bu veri alışverişi P2P ve Collective olabilir. P2P iletişim 2 parçadan oluşur Receive ve Send işlemleri. P2P iletişimin en bilinen türü blocking iletişimdir. 

Blocking iletişim türü kullanımı en kkolay iletişim türlerinden biridir. Kolay yoldur fakat bu sebeple işlemlerin uzun sürmesi kaçınılmazdır.

Mesaj gönderim işlemlerinde ;
* **Buffer referansı :** verinin bulunduğu buffer
* **Veri tipi :** aktarılacak verinin tipi, MPI da  bu veri tipleri ayrıca tanımlıdır.
* **Eleman Sayısı :** Bufferdaki eleman sayısı
* **Tag :** İşlemler arası kurulan iletişimin etiketi, haberleşme işlemine bu tag ile erişilecek.
* **Hedef ID :** Veri göndermek istenen işlemin rank değeri
* **Communicator :** Veri alışveriş işleminin gerçekleşeceği communicator grubu

Alma işlemide yukarıda bahsedilen yapıya benzer bir yapıya sahiptir.

Bu işlemde deadlock durumundan kaçınmak ve buna çok dikkat etmek gerekmektedir. Bir iletişim diğer iletişimi beklerse ve aynı şekilde diğer iletişim de diğer iletişimi beklerse kısır bir bekleme süreci oluşacaktır. 
##### BLOCKING COMMUNICATION UYGULAMASI
...

```sh
int local_value;
local_value = atoi(argv[1]);
int other_value;
```
Parametreleri sıra sıra açıklanacak olursa, uygulama komut ekranından aldığı değeri local_value değerine aktaracaktır. İşlem 0 local_value değerini işlem 1 e gönderecek ve işlem 1 den aldığı değeri ise other_value değerine depolayacaktır.

```sh
MPI_Send(&local_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
```
**Amacı :** İşlemler arası blocking veri iletişimini sağlar.
**Makrrosu :** int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
**Girdi Parametreleri :** 
buf -> gönderilecek verinin başlangıç adresi (opsiyonel)
count -> gönderilen verinin eleman sayısı (unsigned integer)
datatype -> gönderim bufferındaki her elemanın veri tipi
dest -> veri gönderilecek hedef process (integer)
tag -> mesajı iletimini niteleyecek etiket (integer)
comm -> communicator
**Dikkat :** Bu işlem hedef işleme veri iletilesiye kadar akışı bloklayıp durdurabilir.

```sh
MPI_Recv(&other_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
```
**Amacı :** Blocking modda mesaj alır
**Makrosu :** int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag,MPI_Comm comm, MPI_Status * status)
**Çıktı Parametreleri :** 
buf -> alma bufferının başlangıç adresi
status -> durum nesnesi (Status)
**Girdi Parametreleri :** 
count -> alma bufferındaki maksimum eleman sayısı (integer)
datatype -> alma bufferındaki her verinin tipi 
source -> kaynak processin rank değeri (ID)si (integer)
tag -> mesaj etiketi (integer)
comm -> communicator (handle)
**Dikkat :** count argümanı mesajın maksimum uzunluğunu ifade eder, gerçek uzunluj MPI_Get_count ile tanımlanabilir. Bu mesaj uzunluğunu belirleme yöntemlerinden ayrıca bahsedeceğiz.

Bu uygulamada belki kafanızı karıştırmıştır diye ufak bir açıklama yapma istiyorum, if bloklarının kullanım sebebi işlem yapılmak istenen process değerinin belirlenmesidir. **if rank==0** ifadesi ile  o koşul bloğuna sadece o process girecek ve rank ID si 0 olan process diğer process e blocking modda veri aktaracaktır. Diğer process **else** bloğunda çalışacak ve mesaj alma gönderme işlemini gerçekleştirecektir. Kısaca uygulamada process 0, process 1'e veri gönderip alacak ve aynı işlem process 1'de de gerçekleştirilecektir. Aktarılan bu veriler daha sonra toplanarak ekrana yazdırılacaktır.

Bir sonraki konu non-blocking communication konusu olacaktır. Bu derste öğrendiklerinizi araştırarak pekiştirmeden diğer derse devam etmemeniz faydanıza olacaktır. :)

İyi çalışmalar




