N      HOUR     DAY       MONTH  DAYOFWEEK       COMMAND 
#每天早上6点10分 
10    6     *     *     *     date 
#每两个小时 
0     */2   *     *     *     date 
#晚上11点到早上8点之间每两个小时，早上8点 
0     23-7/2，8      *     *     *     date 
#每个月的4号和每个礼拜一到礼拜三的早上11点 
0     11    4     *     1-3  date 
#1月1日早上4点 
0     4     1     1       *  date 
