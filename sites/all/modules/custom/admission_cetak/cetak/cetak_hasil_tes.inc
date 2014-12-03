<?php
function admission_cetak_hasil_form($form, &$form_state){
      $get_value = variable_get('cetak_hasil_conf');
      $def_value = empty($get_value)? NULL:$get_value;
    if(user_access('access admission lihat hasil-test')){
       
        $form['filter']['text'] = array(
            '#title' => 'No. Registrasi',
            '#type' => 'textfield',
            '#size' => 15,
            '#default_value' => $def_value,
        );

        $form['filter']['submit'] = array(
            '#type' => 'submit',
            '#value' => 'Submit'
        );
    }   
    
    if(isset($def_value) OR
            !user_access('access admission lihat hasil-test')){

        $form['output'] = array(
            '#type' => 'markup',
            '#markup' => admission_cetak_hasil_tes($def_value),
        );
    }

   variable_del('cetak_hasil_conf');
   
    return $form;
}

function admission_cetak_hasil_form_submit($form, &$form_state){
    variable_set('cetak_hasil_conf',$form_state['values']['text']);
}
function admission_cetak_hasil_tes($no_test = NULL){
    global $user;
    global $base_path;
   
    if(!is_null($no_test)){
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'node')
                ->entityCondition('bundle', 'registration')
                ->propertyCondition('status', 1)         
                ->fieldCondition('field_reg_no', 'value', $no_test , '=');
        $result = $query->execute();
    }
    else{
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'node')
                ->entityCondition('bundle', 'registration')
                ->propertyCondition('status', 1)         
                ->fieldCondition('field_reg_candidate', 'target_id', $user->uid , '=');
        $result = $query->execute();
    }                  
   
   $output = '';
   $path_gif = $base_path.'sites/default/files/logo_UB.gif';
   
   if(isset($result['node'])){
       $key = array_keys($result['node']);
        $node = node_load($key[0]);
        $uid = $node->uid;

        $profile = profile2_load_by_user($uid);
        $nama = $profile['data_pribadi']->field_personal_fullname['und'][0]['value'];
        $tipe_sekolah = $profile['data_sekolah']->field_sekolah_tipe['und'][0]['value'];
        $nama_sekolah = $profile['data_sekolah']->field_sekolah_sma['und'][0]['value'];
        $asal_sekolah = $tipe_sekolah.' '.$nama_sekolah;
        $kota_sekolah_node = node_load($profile['data_sekolah']->field_sekolah_kota['und'][0]['target_id']);
        $kota_sekolah = $kota_sekolah_node->title;
        
       foreach(element_children($result['node']) as $reg_nid){
           $reg_node = node_load($reg_nid);
           $noreg = $reg_node->field_reg_no['und'][0]['value'];
           
           $output .= "<table border='0' width='100%' cellspacing='0' cellpadding='0'>
                <tbody><tr>
                        <td width='100%' colspan='2'>
                        <img border='0' src=$path_gif width='250' height='42'></td>
                </tr>
                <tr>
                        <td width='17%'>
                        &nbsp;</td>
                        <td width='83%'>&nbsp;</td>
                </tr>
                <tr>
                        <td width='17%'>
                        <p style='margin-top: 5px; margin-bottom: 5px'><font face='Verdana' size='2'>NO. TEST:</font></p></td>
                        <td width='83%'><font size='2' face='Verdana'>$noreg</font></td>
                </tr>
                <tr>
                        <td width='17%'>
                        <p style='margin-top: 5px; margin-bottom: 5px'><font face='Verdana' size='2'>NAMA:</font></p></td>
                        <td width='83%'><font size='2' face='Verdana'>$nama</font></td>
                </tr>
                <tr>
                        <td width='17%'>
                        <p style='margin-top: 5px; margin-bottom: 5px'><font face='Verdana' size='2'>SEKOLAH:</font></p></td>
                        <td width='83%'>
                        <p style='margin-top: 5px; margin-bottom: 5px'>
                        <font size='2' face='Verdana'>$asal_sekolah, $kota_sekolah</font></p></td>
                </tr>";
           
            $query2 = new EntityFieldQuery();
            $query2->entityCondition('entity_type', 'node')
                    ->entityCondition('bundle', 'kelulusan')
                    ->propertyCondition('status', 1)      
                    ->fieldCondition('field_lulus_noreg', 'target_id', $reg_nid , '=');
            $kelulusan = $query2->execute();
            
            //jika admin sudah menentukan kelulusan kandidat maka tampilkan hasilnya
            if(isset($kelulusan['node'])){
                $nid = key($result2['node']);
                $kelulusan_node = node_load($nid);
                
                $text_lulus = '';
                $is_lulus = $kelulusan_node->field_lulus_tes['und'][0]['value'];
                if($is_lulus){
                    $text_lulus .= 'LULUS ';
                    $text_beasiswa = strtoupper($kelulusan_node->field_lulus_kategori['und'][0]['value']);
                    
                    $prodi = node_load($kelulusan_node->field_lulus_prodi['und'][0]['target_id']);
                    $text_prodi = strtoupper($prodi->title);
                    $text_lulus .= $text_beasiswa.' UNTUK PROGRAM '.$text_prodi;
                }
                else{
                    $text_lulus .= 'TIDAK LULUS ';
                }
                $output .="<tr>
                        <td width='17%'>
                        <p style='margin-top: 5px; margin-bottom: 5px'><font face='Verdana' size='2'>HASIL 
                        USM-UB:</font></p></td>
                        <td width='83%'>
                        <font size='2' face='Verdana'>
                        $text_lulus	

                        </font>

                        </td>
                </tr>";
            }
            //jika admin belum menentukan hasil kelulusan
            else{
                $output .="<tr>
                        <td width='17%'>
                        <p style='margin-top: 5px; margin-bottom: 5px'><font face='Verdana' size='2'>HASIL 
                        USM-UB:</font></p></td>
                        <td width='83%'>
                        <font size='2' face='Verdana'>
                        <b>Masih dalam proses.</b>
                        </font>

                        </td>
                </tr>";
            }
           $output .=
                "<tr>
                        <td width='17%'>
                        &nbsp;</td>
                        <td width='83%'>
                        &nbsp;</td>
                </tr>";

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

        $output .= "</tbody></table><br/><br/>";

       }
   }
   else{
       if(in_array('matriculants', $user->roles)) $output .= '<b>Anda belum melakukan Pendaftaran ke UB.<br/> Silakan daftar.</b>';
       if(!in_array('matriculants', $user->roles)) $output .= '<br/><b>Nomor Registrasi Tidak Ada.</b>';
   }
   if($no_test){
       return $output;
   }
    print $output;
}
