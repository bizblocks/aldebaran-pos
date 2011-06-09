select sum(amount) as amount, sum(summ) as sum, orders.id, id_goods, goods.name, id_discount, discount.name, tablenum, timeopen, timeclose, order_table.price from order_table 
		   left join orders on orders.id=id_order 
		   left join goods on id_goods=goods.id 
		   left join discount on id_discount=discount.id 
		   where (orderdate>='2009-05-04') AND (orderdate<='2009-05-04') AND (timeopen>'00:00:00') AND 
		   (timeopen<'23:59:59') AND (status=2 OR status=4) group by orders.id, id_discount, id_goods, goods.name, discount.name, tablenum, timeopen, timeclose, order_table.price 
		   order by orders.id