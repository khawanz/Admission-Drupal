<?php

function admission_cetak_invoice(){
    global $base_path;
    global $user;
    
    $user_id = $user->uid;
    if(!in_array('matriculants', $user->roles)){
        $user_id = arg(2);
    }
    //$current_user = user_load($user_id);
     
   $query = new EntityFieldQuery();
   $query->entityCondition('entity_type', 'node')
           ->entityCondition('bundle', 'registration')
           ->propertyCondition('status', 1)         
           ->fieldCondition('field_reg_candidate', 'target_id', $user_id , '=');
   $result = $query->execute();
   
   //validation
   if(empty($result)){
       return 'PAGE NOT FOUND';
   }
    
    $profile = profile2_load_by_user($user_id);
    $nama = $profile['data_pribadi']->field_personal_fullname['und'][0]['value'];
     //get 'alamat' from field collection
     $items = field_get_items('profile2', $profile['data_pribadi'], 'field_personal_address');
     foreach($items as $item){
         $fc = field_collection_field_get_entity($item);
         $jalan = $fc->field_address_jalan['und'][0]['value'];
         $rtrw = $fc->field_address_rtrw['und'][0]['value'];
         $norumah = $fc->field_address_norumah['und'][0]['value'];
         $kelurahan = $fc->field_address_kelurahan['und'][0]['value'];
         $kecamatan = $fc->field_address_kecamatan['und'][0]['value'];
         $kota_node = node_load($fc->field_address_kota['und'][0]['target_id']);
         $kota = $kota_node->title;
         $kode_pos = $fc->field_address_kodepos['und'][0]['value'];
     }

     $alamat = "Jl. $jalan RT/RW $rtrw No.$norumah, $kelurahan, $kecamatan";  
    
    $output = '<html><head><title>Print Invoice</title>';
    $output .= cetak_invoice_get_style();
    $output .= '</head><body>';
    $output .= '<center><button class=noprint type=button onclick=window.print()>Print</button></center>';

    $path_gif = $base_path.'sites/default/files/logo_UB.gif';
    $tanggal = date('d F y');

    foreach(element_children($result['node']) as $reg_nid){
        $reg_node = node_load($reg_nid);
        $noreg = $reg_node->field_reg_no['und'][0]['value'];
        
        $schedule_node = node_load($reg_node->field_reg_schedule['und'][0]['target_id']);
        $kategori = strtolower($schedule_node->field_schedule_kategori['und'][0]['value']);
        if($kategori == 'jalur usm'){
            $gelombang = $schedule_node->field_schedule_gelombang['und'][0]['value'];
            $waktu = $schedule_node->field_schedule_waktu['und'][0]['value'];
            $waktu = date('d F Y H:i', strtotime($waktu));
            $tempat = $schedule_node->field_schedule_place['und'][0]['value'];
            $kota = $schedule_node->field_schedule_city['und'][0]['value']; 
            //$batas_dokumen = $schedule_node->field_schedule_document['und'][0]['value'];
            $batas_pembayaran = $schedule_node->field_schedule_pembayaran['und'][0]['value'];
            $batas_pembayaran = date('d F Y', strtotime($batas_pembayaran));

            $output .= "

        <table border=0 width=100% cellspacing=0 cellpadding=0>
                <tbody>

                <tr>
                        <td colspan=2>
                      <img border=0 src=$path_gif width=300 height=34><br/><hr/></td>
                </tr>
                <tr>
                        <td colspan=2>
                      <font size=1>&nbsp;</font></td>
                </tr>
                <tr>
                        <td style=border-top: 1px solid #000000 colspan=2>
                        <p align=right><font face=Verdana size=4>INVOICE</font></p></td>
                </tr>
                <tr>
                        <td colspan=2>
                        <p align=right><i><b><font size=1 face=Verdana>Tanggal: $tanggal</font></b></i></p></td>
                </tr>
                <tr>
                        <td width=13%><b><font face=Verdana size=2>NOMOR REG:</font></b></td>
                        <td width=87%><font face=Verdana size=2>$noreg    </font></td>
                </tr>
                <tr>
                        <td width=13%><b><font face=Verdana size=2>NAMA:</font></b></td>
                        <td width=87%><font face=Verdana size=2>$nama</font></td>
                </tr>
                <tr>
                        <td width=13% valign=top><b><font face=Verdana size=2>ALAMAT:</font></b></td>
                        <td width=87%><font face=Verdana size=2>$alamat</font></td>
                </tr>
                <tr>
                        <td width=13%><b><font face=Verdana size=2>KOTA:</font></b></td>
                        <td width=87%><font face=Verdana size=2>$kota</font></td>
                </tr>
                <tr>
                        <td width=13%><b><font face=Verdana size=2>KODE POS:</font></b></td>
                        <td width=87%><font face=Verdana size=2>$kode_pos</font></td>
                </tr>
                <tr>
                        <td width=100% colspan=2>&nbsp;</td>
                </tr>
                <tr>
                        <td width=100% colspan=2>
                        <table border=1 width=100% cellspacing=0 cellpadding=0 style=border-color: #000000>
                                <tbody><tr>
                                        <td style=border-left-style: solid; border-left-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px width=32>
                                        <b><font face=Verdana size=2>NO.</font></b></td>
                                        <td style=border-left-style: solid; border-left-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px>
                                        <b><font face=Verdana size=2>DESKRIPSI</font></b></td>
                                        <td style=border-style: solid; border-width: 1px; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px>
                                        <b><font face=Verdana size=2>TOTAL</font></b></td>
                                </tr>
                                <tr>
                                        <td style=border-left-style: solid; border-left-width: 1px; border-bottom-style: solid; border-bottom-width: 1px; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px width=32 valign=top>
                                        <table border=0 width=100% cellspacing=0 cellpadding=0>
                                                <tbody><tr>
                                                        <td>&nbsp;</td>
                                                </tr>
                                                <tr>
                                                        <td>
                                                        <p align=center>
                                        <font size=2>1.</font></p></td>
                                                </tr>
                                        </tbody></table>
                                        <p align=center>
                                        &nbsp;</p></td>
                                        <td style=border-left-style: solid; border-left-width: 1px; border-bottom-style: solid; border-bottom-width: 1px; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px>
                                        <table border=0 width=100% cellspacing=0 cellpadding=0>
                                                <tbody><tr>
                                                        <td colspan=2>&nbsp;</td>
                                                </tr>
                                                <tr>
                                                        <td colspan=2><p style=margin-left: 10px><font face=Verdana size=2>Biaya 
                                                        pendaftaran Ujian Saringan Masuk Universitas Bakrie</font></p></td>
                                                </tr>
                                                <tr>
                                                        <td width=100% colspan=2>
                                                        <p style=margin-left: 10px>
                                                        <font size=2 face=Verdana>(KHUSUS REGULER)</font></p></td>
                                                </tr>
                                                <tr>
                                                        <td width=19%>&nbsp;</td>
                                                        <td width=81%>&nbsp;</td>
                                                </tr>
                                                <tr>
                                                        <td width=100% align=left colspan=2>
                                                        <p style=margin-right: 5px; margin-left:10px>
                                                        <font face=Verdana size=2><b>
                                                        Gelombang:</b> $gelombang </font></p></td>
                                                </tr>
                                                <tr>
                                                        <td width=100% align=left colspan=2>
                                                        <p style=margin-right: 5px; margin-left:10px>
                                                        <font face=Verdana size=2>
                                                        <b>Tanggal Tes:</b> $waktu</font></p></td>
                                                </tr>
                                                <tr>
                                                        <td width=100% align=left colspan=2>
                                                        <p style=margin-right: 5px; margin-left:10px>
                                                        <font face=Verdana size=2><b>Tempat:</b> $tempat                                                                                             </font></p></td>
                                                </tr>
                                                <tr>
                                                        <td width=100% align=left colspan=2>
                                                        <p style=margin-right: 5px; margin-left:10px>
                                                        <font face=Verdana size=2><b>Kota:</b> $kota                      </font></p></td>
                                                </tr>
                                                <tr>
                                                        <td width=19%>&nbsp;</td>
                                                        <td width=81%>&nbsp;</td>
                                                </tr>
                                                <tr>
                                                        <td width=100% colspan=2>
                                                        <p style=margin-left: 10px>
                                                        <font face=Verdana size=2>Batas 
                                                        Konfirmasi dan Pembayaran: $batas_pembayaran</font></p></td>
                                                </tr>
                                                <tr>
                                                        <td width=100% colspan=2>&nbsp;</td>
                                                </tr>
                                                </tbody></table>
                                        </td>
                                        <td style=border-left-style: solid; border-left-width: 1px; border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px valign=top>
                                        <table border=0 width=100% cellspacing=0 cellpadding=0>
                                                <tbody><tr>
                                                        <td>
                                                        &nbsp;</td>
                                                </tr>
                                                <tr>
                                                        <td>
                                                        <p align=right style=margin-right: 10px>
                                        <font face=Verdana size=2>Rp. 200.000,-</font></p></td>
                                                </tr>
                                                <tr>
                                                        <td>
                                                        <p align=right style=margin-right: 10px>
                                        <font face=Verdana size=2>(Dua ratus ribu rupiah)</font></p></td>
                                                </tr>
                                                <tr>
                                                        <td>&nbsp;</td>
                                                </tr>
                                        </tbody></table>
                                        </td>
                                </tr>
                        </tbody></table>
                        </td>
                </tr>
                <tr>
                        <td width=100% colspan=2>&nbsp;</td>
                </tr>
                <tr>
                        <td width=100% colspan=2>
                        <p style=line-height: 150%><b><font face=Verdana size=2><u>Pembayaran 
                        disetorkan melalui</u>:</font></b></p></td>
                </tr>
                <tr>
                        <td width=100% colspan=2>
                        <p><b><font face=Verdana size=2>Bank Permata</font></b></p></td>
                </tr>
                <tr>
                        <td width=100% colspan=2>
                        <p class=MsoListParagraph style=margin-left: 0in>
                        <font face=Verdana size=2>Cabang Rasuna 
                                        Epicentrum</font></p></td>
                </tr>
                <tr>
                        <td width=100% colspan=2>
                        <p><font face=Verdana size=2>No. Rek. 
                                        070.162.7415</font></p></td>
                </tr>
                <tr>
                        <td width=100% colspan=2>
                        <p><font face=Verdana size=2>Atas Nama: Universitas 
                                        Bakrie</font></p></td>
                </tr>
        </tbody></table><p id=footer></p>";
        }
        
    }    
    
    $output .= '</body></html>';
    
    print $output;
}

function cetak_invoice_get_style(){
     $style = "<style>"
            . "@media print{"
            . ".noprint{"
            . "  display:none"
            . " }"
            . "#footer {"
            . " page-break-after:always;"
             . "}"
            . "}"
            . "</style>";
    
    return $style;
}
