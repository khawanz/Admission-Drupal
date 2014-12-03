<?php

function admission_cetak_jadwal(){
    global $user;
    
    $output = '';
    
//    $schedule_node = node_load(arg(1));
    $reg_nid = arg(2);
    
   $query = new EntityFieldQuery();
   $query->entityCondition('entity_type', 'node')
           ->entityCondition('bundle', 'registration')
           ->propertyCondition('status', 1)
           ->propertyCondition('nid', $reg_nid)
           //->fieldCondition('field_reg_schedule', 'target_id', $schedule_node->nid , '=')
           ->fieldCondition('field_reg_candidate', 'target_id', $user->uid , '=');
   $result = $query->execute();
    
   //validation
   if(empty($result)){
       return 'PAGE NOT FOUND';
   }
   $key = array_keys($result['node']);
   $reg_node = node_load($key[0]);
   $schedule_node = node_load($reg_node->field_reg_schedule['und'][0]['target_id']);
   $penyerahan_dok = $schedule_node->field_schedule_document['und'][0]['value'];
   
   $kategori = strtolower($schedule_node->field_schedule_kategori['und'][0]['value']);
   
    $gelombang = $schedule_node->field_schedule_gelombang['und'][0]['value'];
   
   $output .= "<html><head><title>Print</title>";
   $output .= jadwal_test_get_style_print();
    $output .= "</head><body>";
    $output .= "<table>";
    $output .= "<tr><td align=right><button class=noprint type=button onclick=window.print()>Print</button></td><td></td></tr>";
    $output .= "<tr><td width=300px align=right>Gelombang : </td><td><font color=#8b0101>$gelombang</font></td></tr>";
    
    if($kategori == 'jalur usm'){
       
        $tempat = $schedule_node->field_schedule_place['und'][0]['value'];
        $kota = $schedule_node->field_schedule_city['und'][0]['value'];
        $pembayaran_dok = $schedule_node->field_schedule_pembayaran['und'][0]['value'];

        $datetime = $schedule_node->field_schedule_waktu['und'][0];
        $date_array = explode(' ', $datetime['value']);
        $date = $date_array[0];
        $date_fixed = date('d F Y', strtotime($date));
        $time1 = date('H:i', strtotime($date_array[1]));

        $date_array2 = explode(' ', $datetime['value2']);
        $time2 = date('H:i', strtotime($date_array2[1]));   
   
        $output .= "<tr><td align=right>Tanggal Test : </td><td><font color=#8b0101><font color=#8b0101>$date_fixed</font></font></td></tr>";
        $output .= "<tr><td align=right>Waktu : </td><td><font color=#8b0101>$time1 - $time2</font></td></tr>";
        $output .= "<tr><td align=right valign=top>Tempat : </td><td><font color=#8b0101>$kota, $tempat</font><br/><br/></td></tr>";
    }
    
    
    $batas_dok = date('d F Y',strtotime($penyerahan_dok));
    $output .= "<tr><td align=right valign=top>Batas Penyerahan Dokumen : </td><td><font color=#8b0101>$batas_dok</font><br/><br/></td></tr>";
    
    if($kategori == 'jalur usm'){
        $batas_bayar = date('d F Y', strtotime($pembayaran_dok));
        $output .= "<tr><td align=right valign=top>Batas Pembayaran Biaya Pendaftaran USM : </td><td><font color=#8b0101>$batas_bayar</font><br/><br/></td></tr>";
    
    
    //    $materi = variable_get('materi');
            $output .= "<tr><td align=right valign=top>Materi Test : </td><td><font color=#8b0101>"
                . "1. IPA / IPS<br/>"
                . "2. Matematika dan Bahasa Inggris"
                . "</font><br/><br/></td></tr>";

    //    $perlengkapan = variable_get('perlengkapan');
        $output .= "<tr><td align=right valign=top>Perlengkapan Test : </td><td><font color=#8b0101>"
                . "1. Alat tulis (Pensil 2B, Rautan, Penghapus)<br/>"
                . "2. Kartu Test"
                . "</font><br/><br/></td></tr>";
    }
    
    $output .= "<tr><td align=right valign=top> </td>
                    <td>
                        <font size = 2pt>Informasi lebih lanjut, hubungi:<br/>
                            <strong><font size = 1pt color=#8b0101>Lia/Linggar 021-526 1448 (ext. 118/390)<br/>
                            HP: 0856 777 9945<br/>
                           WA: 0856 777 9945<br/>
                            Line: Universitas Bakrie<br/>
                           Pin BB: 24C112E0</font></strong>
                        <br/><br/>
                     </td></tr>";
    
    $output .= "</table></body></html>";
    
    
    print $output;
}

function jadwal_test_get_style_print(){
    $style = "<style>"
            . "@media print{"
            . ".noprint{"
            . "  display:none"
            . " }"
            . "}"
            . "</style>";
    
    return $style;
}