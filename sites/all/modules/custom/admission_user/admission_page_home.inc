<?php

//Not used. Di cover oleh module panel dengan nama 'frontpage'
function admission_page_home(){
    global $user;
    global $base_url;
    
    $output = '';
    
    $profile = profile2_load_by_user($user->uid);
    
    if($profile){
        $nama = $profile['data_pribadi']->field_personal_fullname['und'][0]['value'];
      
        if($user->uid != 1){
            $output .= "<p>Hallo <b>$nama</b></p>";
        }
        

        if(module_exists('admission_cetak') && isset($profile['kelulusan'])){           
                $output .= "<p><b>Lihat Hasil UMM-UB</b></p>";
        }
        
        if($user->uid != 1){
            $output .= "<p>Username anda adalah $user->name<br/>";
                
            $query = new EntityFieldQuery();
            $query->entityCondition('entity_type', 'node')
                    ->entityCondition('bundle', 'registration')
                    ->propertyCondition('status', 1)
                    ->fieldCondition('field_reg_candidate', 'target_id', $user->uid,'=');
            $result = $query->execute();              

            if(isset($result['node'])){
                $reg_nid = key($result['node']);
                $reg_node = node_load($reg_nid);
                //$user_reg_node = node_load($user_reg_nid[0]);
                if(module_exists('admission_cetak')){
                    $link_schedule = "<a href=$base_url/jadwal>Lihat jadwal</a>";
                    $output .= "Anda terdaftar untuk mengikuti UMM-UB. ($link_schedule)<br/>";
                }
                else{
                     $output .= "Anda terdaftar untuk mengikuti UMM-UB.<br/>";
                }

                 $batas_dok = date('d F Y',strtotime(variable_get('batas_dokumen')));
                 $output .= "Batas akhir penyerahan dokumen persyaratan UMM-UB tanggal <b>$batas_dok</b><br/>";

                 $batas_bayar = date('d F Y', strtotime(variable_get('batas_pembayaran')));
                 $output .= "Batas akhir pembayaran UMM-UB tanggal <b>$batas_bayar</b><br/>";

                 $profile = profile2_load_by_user($user->uid);
                 $total_syarat = count($profile['persyaratan']->field_syarat_dokumen['und']);
                 if($total_syarat != 7){
                     $output .= "Persyaratan kelengkapan dokumen UMM-UB <b>Belum Lengkap, ";
                 }  
                 else{
                     $output .= "Persyaratan kelengkapan dokumen UMM-UB <b>Sudah Lengkap, ";
                 }
                 
                 if($reg_node->field_reg_fee['und'][0]['value'] != 'Paid'){
                     $output .= "Uang Pendaftaran Belum Dibayarkan</b> (Cetak Kartu Tes)";
                 }
                 else if($reg_node->field_reg_fee['und'][0]['value'] == 'Paid'){
                     $output .= "Uang Pendaftaran Sudah Dibayarkan</b> (Cetak Kartu Tes)";
                 }
                 
                 
                $output .= "";
            }
            else{
                $output .= "Anda <font color=red>belum terdaftar</font> sebagai peserta UMM-UB.";
            }
       }

       $output .= "</p>";
    }
    
   
   $output .= views_embed_view('schedule_view');
    
    return $output;
}
