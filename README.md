# joke command q (like unix y)

todo

## usage
* q # 1-qubitを対象に計測して表示
* q -n 5 # 5-qubitを対象に計測して表示
* q -n 5 -m # 5-qubitを対象．計測しない
* q -n 5 -i # 5-qubitを対象で，初期化(計測しない)
* q -n 5 -H 0   # 5-qubitを対象で，qbit[0]にHを適用(計測しない)
* q -n 5 -x 0   # 5-qubitを対象で，qbit[0]にHを適用(計測しない)
* q -n 5 -y 0   # 5-qubitを対象で，qbit[0]にHを適用(計測しない)
* q -n 5 -z 0   # 5-qubitを対象で，qbit[0]にHを適用(計測しない)
* q -n 5 -c 0 -x 1 # 5-qubitを対象に0->1へのC-not(計測しない)

## usage
* パイプでつないで演算したい
* 標準入力から量子数がわかる場合はnをできる(ようにしたい)

* q -n 5 -i | q -n 5 -H 0 | q -n 5 

