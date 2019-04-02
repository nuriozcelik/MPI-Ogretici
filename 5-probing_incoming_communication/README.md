#### PROBING INCOMMING COMMUNICATION
###### !!Önceden açıklamaları yapılan bazı fonksiyonlar açıklanmayacaktır!!
Gerçek uygulamalarda iletişimde kullanılan verilerin boyutları çok fazladır. Bu büyük boyutlu veriye göre bellek kontrolünün ele alınması gerekmektedir. MPI iletişiminde uyulması gereken bazı kurallar vardır.

* Bütün veriyi tek bir iletişimde gruplamaya çalışın. N tane iletişimde M byte veriyi göndermek, tek iletişimde NxM byte veri göndermekten daha zahmetlidir.
* Bufferda saklanılan veri kadar veri gönderilmelidir. Daha fazlası değil.

MPI iletişiminde alıcı kısmın ne kadar veriyi alacağına dair bir fikri yoktur. Bu durumun 3 farklı çözümü vardır.

* Herşeyi 2 iletişimde göndermek, yani önce veri miktarını sonrada veriyi göndermek mantıklı görünüyor olabilir fakat 1. maddenin ihlal edilmesi anlamına gelemktedir.
* Her veri iletişiminde maksimum miktarda buffer kullanarak veri alma, gönderme işleminin yapılması da mantıklı gözükebilir fakat bu da 2. maddeyi ihlal etmektedir.
* Mesajı probelamak, basitçe MPI'a bize ne kadar veri göndereceğini sormak, mantıklı olanı budur. :=)

Probing işlemi çok kullanışlıdır, veri alma işleminde gelen verinin sayısını, ID ve TAG değerlerini bize verir, yada en kötü ihtimalle veri alıp alamadığımız bilgisini verir.

Probing işlemini gerçekleştirmek için 2 farklı fonksiyon vardır, MPI_Probe ve MPI_Iprobe. Tahmin ettiğiniz üzere biri blocking iletişimde diğeri ise non-blocking iletişimde kullanılır.

Bu fonskiyonlara takip edilecek iletişimin tag ve ID değeri verilir ve bu iletişimin status structure'ı bize döndürülür. Daha öncede bahsettiğimiz gibi bu structure tag, Idi count gibi elemanlara sahiptir. Fonksiyona ANY değerleri de verilebilir, bu değerlerden aşağıd bahsedilecektir.


```sh
MPI_Status status;
MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
```
**Amacı :** Mesajı bloklar ve test eder

**Makrosu :** int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status * status)

**Çıktı Parametreleri :** 

status -> status nesnesi

**Girdi Parametreleri :** 

source -> kaynağın ID değeri, veya MPI_ANY_SOURCE olabilir(integer)

tag -> haberleşmenin tag değeri veya MPI_ANY_TAG (integer)

comm -> communicator

```sh
    int n_items;
    MPI_Get_count(&status, MPI_INT, &n_items);
```

**Amacı :** Haberleşmede kullanılan veri sayısını verir

**Makrosu :** int MPI_Get_count(const MPI_Status * status, MPI_Datatype datatype, int *count)

**Çıktı Parametreleri :** 

count -> alınan verini boyutu (integer) 

Dikkat: Veri boyutu sıfır ise, bu rutin sıfır sayısını döndürür. Statusdaki veri miktarı, veri boyutunun tam katı değilse (integer olmaz), fonksiyon MPI_UNDEFINED döndürür.

**Girdi Parametreleri :** 

status -> veri iletisiminde kulanılan status nesnesi, Probe ile elde edilecek.

datatype -> dalma bufferindaki verinin tipi


Kısaca uygulamada Probing Process 1'i bloke eder ve Process 0'dan mesajı bekler. Mesaj ulaştığı anda işlem devam eder. Probing de veri alışverişi gerçekleşmez sadece probing processin alma işlemine hazır olduğu bilgisini verir. MPI_Get_count ise probing ile elde ettiğimiz status nesnesini de kullanarak iletişim için gerekli olan veri boyutunu verir.

Bu sayede ihtiyacımız kadar veri kullanır ve bellekte yer ayırırız.


Bir sonraki konu Communication Modes konusu olacaktır. Bu başlıkta öğrendiklerinizi araştırarak pekiştirmeden diğer başlığa devam etmemeniz faydanıza olacaktır. :)

İyi çalışmalar




