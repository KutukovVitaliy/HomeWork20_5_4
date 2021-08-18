Задание 4. Реализация симуляции банкомата

Что нужно сделать

Требуется реализовать упрощённую симуляцию работы банкомата. В банкомате могут храниться только бумажные 
купюры номиналом от 100 до 5000 рублей. Максимально в банкомате может храниться только 1000 купюр. Все они
записываются в отдельный файл. У банкомата, как у устройства, две основных операции — снятие денег 
пользователем и наполнение деньгами инкассаторами банка.
Наполнение банкомата происходит, если при старте программы в консоль вводится символ плюс “+”.  Количество
купюр рассчитывается так, чтобы банкомат был заполнен полностью. Все купюры при этом выбираются случайным
образом.
Если на старте программы в консоль вводится минус (“-”), то симулируется снятие пользователем денег.
Пользователь указывает сумму с точностью до 100 рублей. Мы будем считать, что каждый клиент обладает
неограниченным балансом в системе и теоретически может снять любую сумму. На практике, если данная сумма
не может быть снята из-за отсутствия подходящих денег в машине, показывается сообщение, что эта операция
невозможна.
После выполнения любой из операций программа завершает выполнение. Состояние банкомата должно храниться
в отдельном бинарном файле, автономно.

Советы и рекомендации

Вы можете хранить массив купюр целиком, помечая отсутствующие позиции нулями.