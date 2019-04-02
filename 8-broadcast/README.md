#### BROADCASTING
###### !!Önceden açıklamaları yapılan bazı fonksiyonlar açıklanmayacaktır!!

Bir işlem aynı bilgiyi tüm diğer işlemlere göndermek istediğinde broadcast gerçekleştirir. Broadcast non-blocking bir işlemdir, süreç, bilgi send/receive olana kadar devam eder. Tüm operasyonlardan sonra bütün işlemler kök işlemden dağılan veriyi kendi bufferlarına kopyalamış olurlar. P2P ile bu işlem N işlem için N adım sürer ve sıralı şekilde devam eder. Broadcast ise bu bilgiyi yayarak dağıtır. (Bu kısmı anlayamadıysanız [buraya](https://www.codingame.com/playgrounds/349/introduction-to-mpi/broadcasting) bakabilirsiniz. 

8 adet işleme bilgi göndermek P2P ile 8 adım sürer.

8 adet işleme bilgi göndermek Bcast ile 4 adım sürer.

Ayrıntılı bilgi için yukarıda paylaştığım linkteki adrese bakabilirsiniz.  

#### Broadcast uygulaması

Bu örnekte 2 işlem iki farklı hesaplama yapacaktır. Her işlemin hesaplamadaki rolü farklı olacaktır. 

İlk aşamada aşağıda görüldüü gibi process 0 veri okuyacak ve bu verileri kendi bufferına atayacaktır. Burada alınacak eleman sayısı alındıktan sonra elemanlar da sırayla alınmaktadır.

```sh
 if (rank == 0) {
    std::cout << "buffer eleman adeti gir"<< std::endl;
    std::cin >> n_elements;
    buffer = new double[n_elements];
    
    for (int i=0; i < n_elements; ++i){
      std::cout << "buffer eleman gir"<<std::endl;
      std::cin >> buffer[i];
    }
  }
```

Daha sonra bu elemanlar ve eleman sayısı diğer işlemlere de dağıtılacaktır. Bu örnekte doğru miktarda veri için bellek de yer ayırmak için eleman sayısı da broadcast yapılmıştır.

```sh
MPI_Bcast(&n_elements, 1, MPI_INT, 0, MPI_COMM_WORLD);
MPI_Bcast(buffer, n_elements, MPI_DOUBLE, 0, MPI_COMM_WORLD);
```

**Amacı :** Communicator içerisindeki diğer işlemlere kök işlemden veri gönderir.

**Makrosu :** int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)

**Çıktı Parametreleri :** 

buffer -> Bufferın başlangıç adresi 

**Girdi Parametreleri :** 

count -> Buffer içerisinde bulunan eleman sayısı (integer)

datatype -> bufferın veri tipi (handle)

root -> veri paylaşılan process in ID si(rank) (integer)

comm -> communicator

Daha sonra tüm processler üzerine düşen işlemleri gerçekletirecektir.

!! tekrar hatırlatayım root veri gönderen processin kimliğidir.


-----------

Bir sonraki konu Reductions konusu olacaktır. Bu başlıkta öğrendiklerinizi araştırarak pekiştirmeden diğer başlığa devam etmemeniz faydanıza olacaktır. :)

İyi çalışmalar




