#### NON-BLOCKING COMMUNICATION
###### !!Önceden açıklamaları yapılan bazı fonksiyonlar açıklanmayacaktır!!
Şimdiye kadar yaptığımız P2P iletişim tekniğinde işlem gönderme-alma işlemini gerçekleştirirken bu işlemlerin tamamlanmasını bekliyordu. Bu beklemeler hızlı processin boşta beklemesini ve sistemin en yavaş işlem biriminin hızına düşmesine sebep oluyordu. Bazı uygulamalarda ve sistemlerde bu çok sınırlayıcı bir durumdur. 2 process düşünelim, bir process tüm hesaplama işlemlerini bitiriyor ve elde ettiği sonucu diğer process'e göndermek istiyor fakat veri göndermek istediği process daha işlemlerini tamamlayıp dinleme konumuna geçmediği için işlemini tamamlayan process yavaş process'i beklemek zorunda kalıyor.

Bu bölümde non-blocking com. ile blocking com. karşılaştırılmalı anlatılacak ve aradaki farkın daha net görülmesi amaçlanacaktır.

Blocking iletişimin çalışma mantığı;

**Process 0**
* 3 saniye çalış
* Process 1 e veri gönder
* 6 saniye çalış
* Process 1 e veri gönder

**Process 1**
* 5 saniye çalış
* Process 0 dan veri al
* 6 saniye çalış
* Proces 0 dan veri al

Blocking communication'da veri gönder-al işlemleri beklemeli yapıldığından bu uygulama uzun süre alacaktır.
##### Blocking Communication Uygulaması
Kod içerisinde yer alan play_blocking_scenario() fonksiyonu bu iletişim tekniği için hazırlnamış bir fonksiyondur. 

```sh
for (int i=0; i < buffer_count; ++i)
    buffer[i] = (rank == 0 ? i*2 : 0);
```

İşlemi ile process 0 içerisinde buffer degiskeni doldurulmaktadır. 
```sh
MPI_Barrier(MPI_COMM_WORLD);
```
**Amacı :** Communicator içindeki tüm işlemler bu fonksiyona ulaşana kadar bloklar.
**Makrrosu :** int MPI_Barrier(MPI_Comm comm)
**Girdi Parametreleri :** 
comm -> communicator
**Dikkat :** Bu fonksiyonu çağıran işlemi durdurur taki tüm işlemler bu fonksiyonu çağırasıya kadar. Tüm işlemler bu fonksiyonu çağırdığında süreç devam eder.

Blocking Communication işleminden kısaca bahsedilmiştir.

##### Non-Blocking Communication Uygulaması
Bu iletişimde işlemini tamamlayan process diğer processi beklemek yerine çalışmaya devam eder ve belli süreler ile diğer process in bitip bitmediğini yoklar. Diğer process de tamamlanmış ise iletişim gerçekleşir.
**Process 0**
* 3 saniye çalış
* Process 1 e veri gönder
    * Process 1 i 1ms de bir kontrol et, iletişime hazır mı dinle
* Process 1 e ikinci veri gönderim işlemini başlat
* Process 1 in verileri almasını bekle

**Process 1**
* 5 saniye çalış
* Process 0 dan alma işlemini başlat
* Process 0 dan iletişimi bekle
* 3 saniye çalış
* Process 0 dan veri al
* Process 0 dan alma işlemini başlat
* Process 0 dan iletişim bekle

```sh
  MPI_Request request;
  MPI_Status  status;
  int request_finished = 0;
  int request_complete = 0;
```
İletişimin durumunun tutulacağı değişkenler ve bayraklar tanımlanmıştır.

```sh
  for (int i=0; i < buffer_count; ++i)
    buffer[i] = (rank == 0 ? i*2 : 0);
```
İletişimde kullanılacak veri hazırlanır.


```sh
MPI_Barrier(MPI_COMM_WORLD);
```
İşlemler hizalanır.

```sh
MPI_Isend(buffer, buffer_count, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
```
**Amacı :** Non-Blocking iletişimde veri gönderir

**Makrosu :** int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag,MPI_Comm comm, MPI_Status * status)

**Çıktı Parametreleri :** 

request -> haberleşme isteği

**Girdi Parametreleri :** 

buf -> gönderme bufferının ilk adresi

count -> alma bufferındaki maksimum eleman sayısı (integer)

datatype -> alma bufferındaki her verinin tipi 

dest -> hedef processin rank değeri (ID)si (integer)

tag -> mesaj etiketi (integer)

comm -> communicator (handle)

```sh
if (!request_complete) {
          MPI_Test(&request, &request_complete, &status);
      }
```
**Amacı :** İsteğin tamamlanıp tamamlanmadığını test eder

**Makrosu :** int MPI_Test(MPI_Request * request, int *flag, MPI_Status * status)

**Çıktı Parametreleri :** 

flag -> operasyon tamamlanmış ise true(1) döner (logical)

status -> status nesnesi (Status). Kullanılmak istenmediği durumlarda MPI_STATUS_IGNORE olabilir.

**Girdi Parametreleri :** 

request -> MPI talebi



```sh
if (!request_complete){
            MPI_Wait(&request, &status);
        }
```
**Amacı :** Talep tamamlanasıya kadar MPI'yı bekletir.

**Makrosu :** int MPI_Wait(MPI_Request *request, MPI_Status *status)

**Çıktı Parametreleri :** 

status -> status nesnesi (Status). Kullanılmak istenmediği durumlarda MPI_STATUS_IGNORE olabilir.

**Girdi Parametreleri :** 

request -> MPI talebi

Burada biraz MPI_Status ve MPI_Request structurelarından bahsetmek istiyorum. Bu yapılar yukarıda kullanımında da gördüğümüz üzere MPI_Status: alınan mesajın durumunu temsil eder. MPI_Request: iletişim talebini temsil eder.

Ayrıntılı şekilde bakacak olursak;


```sh
typedef struct MPI_Status {
     int count; //alınan içeriğin sayısı
     int cancelled;//talebin iptal edilip edilmediine dair gösterge
     int MPI_SOURCE;//mesajın geldiği islemci ID si
     int MPI_TAG;//veri aktarılan iletisimin etiket değeri
     int MPI_ERROR;//Mesaj ile alakalı hata
} MPI_Status;
```
Structure'ı mpi.h başlık dosyasının 306. satırında tanımlanmış bir yapıdır. 

```sh
/* MPI request opjects */
typedef int MPI_Request;
```
MPI_Request integer sınıfından türetilmis bir tipdir. 


```sh
MPI_Irecv(buffer, buffer_count, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
```

**Amacı :** Non-Blocking iletişimde veri alır

**Makrosu :** iint MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request * request)

**Çıktı Parametreleri :** 

request -> haberleşme isteği

**Girdi Parametreleri :** 

buf -> gönderme bufferının ilk adresi

count -> alma bufferındaki maksimum eleman sayısı (integer)

datatype -> alma bufferındaki her verinin tipi 

source -> kaynak processin rank değeri (ID)si (integer)

tag -> mesaj etiketi (integer)

comm -> communicator (handle)

Kısaca açıklamak gerekirse, birbirini bloklamayan işlemler arası bir iletişim oluşturulmaya çalışılmıştır. Haberleşme başladığı anda bir request oluşturulmuştur. Her iki taraf da hazır olduğunda bu request 1 olacaktır, bu sebeple bu requestin işlemler içinde sürekli takip edilmesi gerekmektedir. Bu requestin tamamlanabilmesi için MPI_Wait ve MPI_Test fonksiyonları kullanılır. MPI_Test process de işlemler devam ederken arada gider talebi yoklari MPI_Wait ise son çare olarak bu talebin tamamlanmasını bekler. Bu request bu iki fonksiyon kullanılarak mutlaka tamamlanmalıdır. Bu iki fonksiyonun farklı çeşitleri mevcuttur, burada bahsedilmeyen diğer fonksiyonları da okuyup anlamanızı öneririm.


Bir sonraki konu Race Conditions konusu olacaktır. Bu başlıkta öğrendiklerinizi araştırarak pekiştirmeden diğer başlığa devam etmemeniz faydanıza olacaktır. :)

İyi çalışmalar




