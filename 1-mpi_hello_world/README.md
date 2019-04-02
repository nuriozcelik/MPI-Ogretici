# MPI HELLO WORLD
##### MPI Nedir?
MPI(Message Passing Interface) kabaca, aynı kodun farklı bilgisayarlar, işlemciler, çekirdekler üzerinde çalışması istendiği durumlarda kullanılan bir protokoldür. Paralel programla zahmetli ve zor bir iş olduğundan bu durumu kontrol altında tutmak için bir standart belirlenmiş ve bazı kurallar konulmuştur. Sonuçta da MPI protokolü doğmuştur, bu protokolün implemente edildiği farklı farklı kütüphanler uygulamalar söz konusudur.

##### MPI Terimleri
Uygulamada karşınıza çıkacak bazı terimleri şimdiden açıklamakta fayda görüyorum. Bu terimler
* **Communicator :** Birbiri ile iletişim kurma yeteneğine sahip olacak işlemleri gruplamaya yarayan etikettir.
* **Rank :** Her işlem grubu eşsiz bir sayı değeri alır, her işlem diğer işlem ile bu değere göre iletişim kurar bu ID'ye **rank** denir.
* **Size :** İşlemlerin adetini temsil eden değerdir. Uygulamada çalışan process saysısı olarak düşünülebilir.

MPI işlemler arasında mesaj gönderme ve alma felsefesi üzerine kurulu bir sistemdir. Her işlem mesajını yukarıda bahsi geçen değerler doğrultusunda gönderir veya alır. Belli bir rank değerine sahip bir işlem belli bir rank değerine sahip diğer bir işleme direk olarak mesaj gönderebilir. Bu durumlardan ilerleyen konularda ayrıntılı olarak bahsedilecektir.
MPI'ın farklı varyasyonları yukarıda da bahsedildiği üzere mevcuttur, bunlardan en çok kullanılanı ise MPICH2 dir.
```sh
brew install mpich2
```
Komutunu ve brew i kullanarak bilgisayarınıza hızlıca yükleyebilirsiniz. Windows için [buraya](http://swash.sourceforge.net/online_doc/swashimp/node9.html) bakabilirsiniz. Yükleme tamamlandıktan sonra **mpiexec --version** komutu ile yüklemenin doğruluğunu teyit edebilirsiniz.

Kısaca MPI çalıştırıldığında, işlemler communicator'lar altında gruplanır, bu communicatorlar işlemleri bir arada tutan kutular gibidir, aynı communicator altında bulunan işlemlerin iletişimine izin verir. 
MPI'da iletişimler iki türde olabilir. 
* **Point to Point :** Aynı communicator altında bulunan iki işlemin iletişime geçmesi.
* **Collective :** Communicator altında bulunan tüm işlemlerin birbiri ile iletişime geçmesi.

MPI'da MPI_COMM_WORLD varsayılan communicator dür. Temel olarak processler başlangıçta bu communicator altında [linkte](http://www.rc.usf.edu/tutorials/classes/tutorial/mpi/images/groups.jpg) olduğu gibi gruplanırlar. MPI_COMM_WORLD tek communicator değildir istenilen durumlarda kendi communicatorlarımızı oluşturmamızda mümkündür.

##### MPI HELLO WORLD UYGULAMASI
mpi_hello_world.c uygulamamıza gelecek olursak, 
```sh
MPI_Init(&arg, &argv);
```
**Amacı :** MPI ortamını başlatır. 
**Markrosu :** int MPI_Init( int *argc, char ***argv )
**Girdi Parametreleri :** 
argc -> argüman saysının pointerı
argv -> argüman vektörünün pointerı
**Dikkat :** Bu fonksiyon sadece ana thread içinde yani main thread da çağırılmalıdır. Devamında da MPI_Finalize çağırılmadırı.
```sh
MPI_Comm_size(MPI_COMM_WORLD, &size);
```
**Amacı :** Communicator ile ilişkili olan grubun boyutunu tanımlamak için kullanılır.
**Markrosu :** int MPI_Comm_size( MPI_Comm comm, int *size ) 
**Girdi Parametreleri :** 
comm -> boyutu öğrenilecek olan communicator 
**Çıktı Parametreleri :** 
size -> communicator grubundaki işlem sayısı (integer)

```sh
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
```
**Amacı :** Communicator da işletilen process in rankını tanımlamak amacıyla kullanılır.
**Markrosu :** int MPI_Comm_rank( MPI_Comm comm, int *rank ) 
**Girdi Parametreleri :** 
comm -> boyutu öğrenilecek olan communicator 
**Çıktı Parametreleri :** 
size -> communicator grubunda işletilen işlemin rank değeri (integer)

```sh
printf("Islem #%d den merhaba :))\n", rank);
```
O anda kaç tane işlem çalıştırılyorsa o sayı kadar ekranda **Islem #x den merhaba :)** yazacaktrır. Bu sayı o anki işlemin Uniq ID sini temsil etmektedir. Yani o anda işletilen işlemin ID değerini.

```sh
if(rank == 0){
        printf("islemin size degeri #%d dir. \n", size);
    }
```
Eşiz kimliği 0 olan işlemin işletilmesi anında ekrana communicator içerisinde işletilen işlemlerin sayısı yazdırılacaktır.

```sh
MPI_Finalize();
```
**Amacı :** MPI ortamını sonlandırır. 
**Markrosu :** int MPI_Finalize( void )
**Dikkat :** Tüm işlemler bitiminde bu fonksiyonu mutlaka çağırmalıdır. Bu fonskiyon sadece MPI_Init fonksiyonunu çağırıldığı thread içerisinde çağırılmalıdır.


Bir sonraki konu blocking communication konusu olacaktır. Bu derste öğrendiklerinizi araştırarak pekiştirmeden diğer derse devam etmemeniz faydanıza olacaktır. :)

İyi çalışmalar




