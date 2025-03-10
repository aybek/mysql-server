--echo connect (master,127.0.0.1,root,,test,MASTER_MYPORT);
connect (master,127.0.0.1,root,,test,$MASTER_MYPORT);
--echo connect (slave,$IPv6,root,,test,SLAVE_MYPORT);
connect (slave,$IPv6,root,,test,$SLAVE_MYPORT);
--echo connection master;
connection master;
reset binary logs and gtids;
source include/show_master_status.inc;
save_master_pos;
--echo connection slave;
connection slave;
reset slave;
let $master_host= query_get_value(SHOW REPLICA STATUS, Source_Host, 1);
--echo Master-Host: $master_host
eval CHANGE REPLICATION SOURCE to SOURCE_HOST='$IPv6';
let $master_host= query_get_value(SHOW REPLICA STATUS, Source_Host, 1);
--echo Master-Host: $master_host
--echo disconnect slave;
disconnect slave;
--echo disconnect master;
disconnect master;
--echo connection default;
connection default;

