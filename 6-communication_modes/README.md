#### COMMUNICATION MODES

P2P iletişime dair çoğu işlemi görmüş durumdayız. İletişimin de bazı modları vardır.

Bu modlar,

Standart Mode : MPI_Send, Mod seçilmeyen durumda kullanılır ve MPI bu fonksiyonun kullanılması durumunda veri boyutuna göre otomatik olarak mod belirler, veri boyutu arttıkça senkron moda yaklaşır.

Buffered Mode : MPI_Bsend

Ready_Mode    : MPI_Rsend

Synchrounous Mode : MPI_Ssend

Uygulamada da fark edeceğiniz üzere veri az iken gönderme işlemi tamamlanıp alma işlemi gerçekleşirken, veri boyutu artınca sanki bu iki işlem de aynı anda oluyormuş gibi bir durum söz konusudur. Uygulamada bu modları deneyerek sonuçları inceleyebilirsiniz. 

P2P iletişimi tamamladığımız için colective iletişime geçeceğiz. Bu başlıkta öğrendiklerinizi araştırarak pekiştirmeden diğer başlığa devam etmemeniz faydanıza olacaktır. :)

İyi çalışmalar




