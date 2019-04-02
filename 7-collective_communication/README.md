#### COLLECTIVE COMMUNICATION

Önceki örneklerde işlemden işleme mesaj gönderme durumları ele alınmıştı. Bazı durumlarda çok sayıda işlem arasında genel bir mesajı paylaşma durumu söz konusu olabilir. collective_communicatin_p2p.cpp örneğinde işlemler arasında p2p tekniği ile iletişim kurulmuş ve bir işlemden diğer işlemlere sırayla mesaj gönderme işlemi gerçekleştirilmiştir.


```sh
for (int id_dest=1; id_dest < size; ++id_dest)
    MPI_Send(buffer, 5, MPI_INT, id_dest, 0, MPI_COMM_WORLD);
```
ile işlem sayısı kadar mesaj gönderme işlemi gerçekleştirilmiş ve diğer tüm işlemler bu değişkenden haberdar edilmiştir. Her işleme bir işlemden sıra ile veri gönderme işlemi zahmetli bir işlemdir, daha kolay ve kabul edilebilir bir örneği collective communication da mevcuttur.

Collective communication işlemler ve communiccatorlar arasında veri alış verişini kolaylaştırır. Farklı tipte ve farklı amaçlara hitap eden communication tipleri mevcuttur.

* Broadcast : Tek process diğer bütün processlere veri gönderebilir
* Reduction : Bir process diğer tüm processlerden mesaj alır ve u veri üzerinde işlem yapar(toplama, max, min vb.)
* Scatter : Tek process veriyi parçalar ve bu parçaları diğer processlere gönderir.
* Gather : Tek process diğer processlerden gelen parçalı verileri birleştirerek bufferda saklar.

collective_communication_bcast.cpp örneğindeki MPI_Bcast fonksiyonu blocking modda çalışmaktadır. Non blocking mod için MPI_Ibcast kullanılabilir. (MPI_Test ve MPI_Wait unutulmamalı)




 Bu başlıkta öğrendiklerinizi araştırarak pekiştirmeden diğer başlığa devam etmemeniz faydanıza olacaktır. :)

İyi çalışmalar




