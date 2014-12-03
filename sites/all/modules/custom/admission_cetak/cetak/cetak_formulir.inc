<?php

function admission_cetak_formulir(){
    global $base_path;
    global $user;

    $user_id = $user->uid;
    if(!in_array('matriculants', $user->roles)){
        $user_id = arg(2);
    }
    $current_user = user_load($user_id);
    
   $query = new EntityFieldQuery();
   $query->entityCondition('entity_type', 'node')
           ->entityCondition('bundle', 'registration')
           ->propertyCondition('status', 1)         
           ->fieldCondition('field_reg_candidate', 'target_id', $user_id , '=');
   $result = $query->execute();
   
   //validation
   if(empty($result)){
       drupal_set_message('Silakan lakukan pendaftaran dengan mengikuti ujian masuk atau seleksi melalui jalur khusus (rapor/UN).');
       return '';
   }
    
   $output = '<html><head><title>Print Formulir Pendaftaran</title>';
   $output .= cetak_formulir_get_style();
   $output .= '</head><body>';

   $path_gif = $base_path.'sites/default/files/logo_UB.gif';

   $output .= '<center><button class=noprint type=button onclick=window.print()>Print</button></center>';
   
   $profile = profile2_load_by_user($user_id);
   
   //DATA PRIBADI
   $nama = $profile['data_pribadi']->field_personal_fullname['und'][0]['value'];
   $tempat_lahir = $profile['data_pribadi']->field_personal_birthplace['und'][0]['value'];
   $tanggal_lahir = $profile['data_pribadi']->field_personal_birthdate['und'][0]['value'];
   $tgl_lahir_text = date('d M Y', strtotime($tanggal_lahir));
   
   $agama = $profile['data_pribadi']->field_personal_religion['und'][0]['value'];
   $status = $profile['data_pribadi']->field_personal_status['und'][0]['value'];
   $jenis_kelamin = $profile['data_pribadi']->field_personal_sex['und'][0]['value'];
   $telepon1 = $profile['data_pribadi']->field_personal_telp['und'][0]['value'];
   $telepon = isset($telepon1)? $telepon1:'-';
   $hp = $profile['data_pribadi']->field_personal_hp['und'][0]['value'];
   $email = $current_user->mail;
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
   
   //DATA ORANGTUA
   $nama_orangtua = $profile['data_orangtua']->field_orangtua_nama['und'][0]['value'];
   $pendidikan = $profile['data_orangtua']->field_orangtua_pendidikan['und'][0]['value'];
   $pekerjaan = $profile['data_orangtua']->field_orangtua_pekerjaan['und'][0]['value'];
   $jabatan = $profile['data_orangtua']->field_orangtua_jabatan['und'][0]['value'];
   $telp_kantor = $profile['data_orangtua']->field_orangtua_telpkantor['und'][0]['value'];
   $telp_rumah = $profile['data_orangtua']->field_orangtua_telprumah['und'][0]['value'];
   $hp_orangtua = $profile['data_orangtua']->field_orangtua_hp['und'][0]['value'];
   $email_orangtua = isset($profile['data_orangtua']->field_orangtua_email['und'][0]['value'])?
           $profile['data_orangtua']->field_orangtua_email['und'][0]['value']:0;
   $alamat_orangtua = $profile['data_orangtua']->field_orangtua_alamat['und'][0]['value'];
   $kota_orangtua_node = node_load($profile['data_orangtua']->field_orangtua_kota['und'][0]['target_id']);
   $kota_orangtua = $kota_orangtua_node->title;
   $kodepos_orangtua = $profile['data_orangtua']->field_orangtua_kodepos['und'][0]['value'];
   
   //DATA SEKOLAH
   $tipe = $profile['data_sekolah']->field_sekolah_tipe['und'][0]['value'];
   $nama_sma = $profile['data_sekolah']->field_sekolah_sma['und'][0]['value'];
   $sma = $tipe.' '.$nama_sma;
   $jurusan = strtoupper($profile['data_sekolah']->field_sekolah_jurusan['und'][0]['value']);
   $tahunlulus = $profile['data_sekolah']->field_sekolah_tahunlulus['und'][0]['value'];
   $tahunlulus = date('Y', strtotime($tahunlulus));
   $alamat_sma = $profile['data_sekolah']->field_sekolah_alamat['und'][0]['value'];
   $kota_sma_node = node_load($profile['data_sekolah']->field_sekolah_kota['und'][0]['target_id']);
   $kota_sma = $kota_sma_node->title;
   $kodepos_sma = $profile['data_sekolah']->field_sekolah_kodepos['und'][0]['value'];
    
   foreach(element_children($result['node']) as $reg_nid){
       $reg_node = node_load($reg_nid);
       $noreg = $reg_node->field_reg_no['und'][0]['value'];
       $nomor_file = isset($reg_node->field_reg_fileno['und'][0]['value'])?
            $reg_node->field_reg_fileno['und'][0]['value']:'-';
       
       $schedule_node = node_load($reg_node->field_reg_schedule['und'][0]['target_id']);
       $schedule_node_title = $schedule_node->title;
       
       $jurusan1 = node_load($reg_node->field_reg_departement1['und'][0]['target_id'])->title;
//       $jurusan2 = node_load($reg_node->field_reg_departement2['und'][0]['target_id'])->title;
//       $jurusan3 = node_load($reg_node->field_reg_departement3['und'][0]['target_id'])->title;
       
       $output .= "<table border='1' cellpadding='0' cellspacing='10' style='border-collapse: collapse' bordercolor='#C0C0C0' width='100%' id='AutoNumber5'>
        <tbody><tr>
          <td width='100%'>
          <table border='0' cellpadding='0' cellspacing='0' style='border-collapse: collapse; border-width: 0' bordercolor='#111111' width='100%' id='AutoNumber6'>
            <tbody><tr>
              <td width='47%' style='border-style: none; border-width: medium' colspan='2'>
                    <img border='0' src=$path_gif width='300' height='34'></td>
              <td width='53%' style='border-style: none; border-width: medium' rowspan='9' align='right' valign='top'>
              <i>
              <font size='1' face='Verdana'>

                      </font></i></td>
            </tr>
            <tr>
              <td width='47%' style='border-style: none; border-width: medium' colspan='2'>
                      <font size='1'>&nbsp;</font></td>
            </tr>
            <tr>
              <td width='47%' style='border-style: none; border-width: medium' colspan='2' height='17'>
                    <font face='Verdana' size='2'>FORMULIR PENDAFTARAN MAHASISWA BARU</font></td>
            </tr>
            <tr>
              <td width='9%' style='border-style: none; border-width: medium'>&nbsp;</td>
              <td width='38%' style='border-style: none; border-width: medium'>&nbsp;</td>
            </tr>
            <tr>
                    <td width='13%' style='border-style: none; border-width: medium' height='10'>
                    <p style='margin-right:10; margin-top:1; margin-bottom:1' align='right'>
                                      <font face='Verdana' size='1'>Nomor:</font></p></td>
                    <td width='38%' style='border-style: none; border-width: medium'>
                    <font size='1' face='Verdana' color='#000080'>
                    $noreg             
                    </font><font size='1'>&nbsp;</font></td>
            </tr>
            <tr>
                    <td width='13%' style='border-style: none; border-width: medium' height='10'>
                    <p style='margin-right:10; margin-top:1; margin-bottom:1' align='right'><font size='1' face='Verdana'>
                    Gelombang:</font></p></td>
                    <td width='38%' style='border-style: none; border-width: medium'>

                    <font size='1' face='Verdana' color='#000080'>$schedule_node_title </font><font size='1'>             

                    </font><font size='1'>&nbsp;</font></td>
            </tr>
            <tr>
                    <td width='13%' style='border-style: none; border-width: medium' height='1'>
                    <p style='margin-right:10; margin-top:1; margin-bottom:1' align='right'><font size='1' face='Verdana'>
                    Pilihan Jurusan 1:</font></p></td>
                    <td width='38%' style='border-style: none; border-width: medium'>
                    <font size='1' face='Verdana' color='#000080'>
                    $jurusan1             

                    </font><font size='1'>&nbsp;</font></td>
            </tr>";
//            <tr>
//                    <td width='13%' style='border-style: none; border-width: medium' height='1'>
//                    <p style='margin-right:10; margin-top:1; margin-bottom:1' align='right'><font size='1' face='Verdana'>
//                    Pilihan Jurusan 2:</font></p></td>
//                    <td width='38%' style='border-style: none; border-width: medium'>
//                    <font size='1' face='Verdana' color='#000080'>
//                    $jurusan2              
//
//                    </font><font size='1'>&nbsp;</font></td>
//            </tr>
//            <tr>
//                    <td width='13%' style='border-style: none; border-width: medium' height='1'>
//                    <p style='margin-right:10; margin-top:1; margin-bottom:1' align='right'><font size='1' face='Verdana'>
//                    Pilihan Jurusan 3:</font></p></td>
//                    <td width='38%' style='border-style: none; border-width: medium'>
//                    <font size='1' face='Verdana' color='#000080'>
//                    $jurusan3              
//
//                    </font><font size='1'>&nbsp;</font></td>
//            </tr>
            $output .= "<tr>
                    <td width='13%' style='border-style: none; border-width: medium' height='1'>
                    <p align='right' style='margin-right: 10px'>
                                      <font face='Verdana' size='1'>&nbsp;</font></p></td>
                    <td width='38%' style='border-style: none; border-width: medium'>
                    <font face='Verdana' size='1' color='#000080'>
                    Reguler
                    </font></td>
            </tr>
            <tr>
                    <td width='13%' style='border-style: none; border-width: medium' height='1'>
                    <p align='right' style='margin-right: 10px; margin-top:1px; margin-bottom:1px'>
                                      <font size='1' face='Verdana'>Nomor File:</font></p></td>
                    <td width='38%' style='border-style: none; border-width: medium'>
                    <font size='1' face='Verdana' color='#000080'>    $nomor_file      </font></td>
            </tr>
            <tr>
                    <td width='103%' style='border-style: none; border-width: medium' height='1' colspan='3'>
                    <font size='1'>&nbsp;</font></td>
                    </tr>
            <tr>
                    <td width='103%' style='border-style: none; border-width: medium' height='1' colspan='3'>
                    <table border='0' cellpadding='0' cellspacing='0' style='border-collapse: collapse; border-width: 0' bordercolor='#111111' width='100%' id='AutoNumber9'>
                      <tbody><tr>
                        <td width='354' style='border: 1px solid #C0C0C0' colspan='2' height='16'>
                        <p align='center'><b>
                    <font size='2' face='Verdana'>DATA PRIBADI</font></b></p></td>
                        <td width='25' style='border-style: none; border-width: medium' rowspan='15' height='89'>
                        <font size='1'>&nbsp;</font></td>
                        <td width='468' style='border: 1px solid #C0C0C0' colspan='2' height='16'>
                        <p align='center'><b>
                    <font size='2' face='Verdana'>DATA ORANG TUA / WALI</font></b></p></td>
                      </tr>
                      <tr>
                        <td width='469' style='border-left:medium none #C0C0C0; border-right:medium none #C0C0C0; border-top:1px solid #C0C0C0; border-bottom:medium none #C0C0C0; ' colspan='2' height='11'>
                        <font size='1'>&nbsp;</font></td>
                        <td width='469' style='border-left:medium none #C0C0C0; border-right:medium none #C0C0C0; border-top:1px solid #C0C0C0; border-bottom:medium none #C0C0C0; ' colspan='2' height='11'>
                        <font size='1'>&nbsp;</font></td>
                      </tr>
                      <tr>
                  <td width='124' style='border-style: none; border-width: medium' height='12'>
                  <p align='right' style='margin-right:10; margin-top:1; margin-bottom:1'>
                  <font size='1' face='Verdana'>Nama Lengkap:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' face='Verdana' color='#000080'>$nama</font><font size='1'>
                        </font><font size='1'>&nbsp;</font></td>
                  <td width='117' style='border-style: none; border-width: medium' height='12'>
                  <p align='right' style='margin-right:10; margin-top:1; margin-bottom:1'>
                  <font size='1' face='Verdana'>Nama Lengkap:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' face='Verdana' color='#000080'>$nama_orangtua</font></td>
                      </tr>
                      <tr>
                  <td width='124' style='border-style: none; border-width: medium' align='right' height='1'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Tempat 
                  Lahir:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='1'>
                        <font size='1' face='Verdana' color='#000080'>$tempat_lahir</font><font size='1'>
                        </font><font size='1'>&nbsp;</font></td>
                  <td width='117' style='border-style: none; border-width: medium' align='right' height='1'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>
                  Pendidikan:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='1'>
                        <font size='1' color='#000080' face='Verdana'>
                    $pendidikan                  
                        </font></td>
                      </tr>
                      <tr>
                  <td width='124' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Tanggal 
                  Lahir:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' face='Verdana' color='#000080'>$tgl_lahir_text</font><font size='1'>
                        </font><font size='1'>&nbsp;</font></td>
                  <td width='117' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Pekerjaan:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' color='#000080' face='Verdana'>$pekerjaan                                               </font></td>
                      </tr>
                      <tr>
                  <td width='124' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Agama:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' face='Verdana' color='#000080'>
                   $agama	                
                        </font><font size='1'>&nbsp;</font></td>
                  <td width='117' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Jabatan:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' color='#000080' face='Verdana'>$jabatan                                      </font></td>
                      </tr>
                      <tr>
                  <td width='124' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Status:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' face='Verdana' color='#000080'>
                    $status                  
                        </font><font size='1'>&nbsp;</font></td>
                  <td width='117' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Telp 
                  Kantor:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' color='#000080' face='Verdana'>$telp_kantor</font></td>
                      </tr>
                      <tr>
                  <td width='124' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Jenis 
                  Kelamin:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' face='Verdana' color='#000080'>
                    $jenis_kelamin                    
                        </font><font size='1'>&nbsp;</font></td>
                  <td width='117' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Telp 
                  Rumah:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' color='#000080' face='Verdana'>$telp_rumah</font></td>
                      </tr>
                      <tr>
                  <td width='124' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Telepon:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' face='Verdana' color='#000080'>$telepon</font><font size='1'>
                        </font><font size='1'>&nbsp;</font></td>
                  <td width='117' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>HP:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' color='#000080' face='Verdana'>$hp</font></td>
                      </tr>
                      <tr>
                  <td width='124' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>HP:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' face='Verdana' color='#000080'>$hp_orangtua</font><font size='1'>
                        </font><font size='1'>&nbsp;</font></td>
                  <td width='117' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Email:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' color='#000080' face='Verdana'>$email                                                                           &nbsp;</font></td>
                      </tr>
                      <tr>
                  <td width='124' style='border-style: none; border-width: medium' align='right' height='12'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Email:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' face='Verdana' color='#000080'>$email_orangtua </font><font size='1'>
                        </font><font size='1'>&nbsp;</font></td>
                  <td width='117' style='border-style: none; border-width: medium' align='right' height='12' valign='top'>
                  <p align='left'>
                  <font size='1'>&nbsp;&nbsp; </font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='12'>
                        <font size='1' color='#000080' face='Verdana'>&nbsp;</font></td>
                      </tr>
                      <tr>
                  <td width='124' style='border-style: none; border-width: medium' align='right' height='1' valign='top'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Alamat:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='1'>
                        <font size='1' face='Verdana' color='#000080'>$alamat</font><font size='1'>
                        </font></td>
                  <td width='117' style='border-style: none; border-width: medium' align='right' height='1' valign='top'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Alamat:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='1' valign='top'>
                        <font size='1' color='#000080' face='Verdana'>$alamat_orangtua&nbsp;</font></td>
                      </tr>
                      <tr>
                  <td width='124' style='border-style: none; border-width: medium' align='right' height='1'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Kota:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='1'>
                        <font size='1' face='Verdana' color='#000080'>$kota</font><font size='1'>
                        </font></td>
                  <td width='117' style='border-style: none; border-width: medium' align='right' height='1'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Kota:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='1'>
                        <font face='verdana' size='1' color='#000080'>$kota_orangtua</font></td>
                      </tr>                                    
                      <tr>
                  <td width='124' style='border-style: none; border-width: medium' align='right' height='1'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Kode Pos:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='1'>
                        <font face='Verdana' size='1' color='#000080'>$kode_pos</font></td>
                  <td width='117' style='border-style: none; border-width: medium' align='right' height='1'>
                  <p style='margin-right:10; margin-top:1; margin-bottom:1'><font face='Verdana' size='1'>Kode Pos:</font></p></td>
                        <td width='345' style='border-style: none; border-width: medium' height='1'>
                        <font size='1' color='#000080' face='Verdana'>$kodepos_orangtua&nbsp;</font></td>
                      </tr>
                      <tr>
                  <td width='963' style='border-style: none; border-width: medium' align='right' height='10' colspan='5'>
                        <font size='1'>&nbsp;</font></td>
                      </tr>
                      <tr>
                  <td width='467' style='border:1px solid #C0C0C0; ' align='right' height='16' colspan='2'>
                        <p align='center'><b><font size='2' face='Verdana'>DATA 
                    SEKOLAH</font></b></p></td>
                        <td width='25' style='border-style: none; border-width: medium' rowspan='3' height='154'>&nbsp;</td>
                  <td width='468' style='border:1px solid #C0C0C0; ' align='right' height='16' colspan='2'>
                        <p align='center'><b><font size='2' face='Verdana'>DOKUMEN 
                        PENDUKUNG</font></b></p></td>
                      </tr>
                      <tr>
                  <td width='469' style='border-left:medium none #C0C0C0; border-right:medium none #C0C0C0; border-top:1px solid #C0C0C0; border-bottom:medium none #C0C0C0; ' align='right' height='11' colspan='2'>
                        <p align='center'><font size='1'>&nbsp;</font></p></td>
                  <td width='469' style='border-left:medium none #C0C0C0; border-right:medium none #C0C0C0; border-top:1px solid #C0C0C0; border-bottom:medium none #C0C0C0; ' align='right' height='11' colspan='2'>
                        <font size='1'>&nbsp;</font></td>
                      </tr>
                      <tr>
                  <td width='469' style='border-style: none; border-width: medium' align='right' height='125' colspan='2' valign='top'>
                        <table border='0' cellpadding='0' cellspacing='0' style='border-collapse: collapse; border-width: 0' bordercolor='#111111' width='100%' id='AutoNumber10'>
                          <tbody><tr>
                  <td width='27%' style='border-style: none; border-width: medium' height='4'>
                  <p align='right' style='margin-top:1; margin-bottom:1; margin-right:10'>
                  <font face='Verdana' size='1'>SMA Asal:</font></p></td>
                            <td width='103%' style='border-style: none; border-width: medium'>
                            <font size='1' face='Verdana' color='#000080'>$sma</font><font size='1'>
                            </font><font size='1'>&nbsp;</font></td>
                          </tr>
                          <tr>
                  <td width='27%' style='border-style: none; border-width: medium' align='right' height='1'>
                  <p style='margin-top:1; margin-bottom:1; margin-right:10'><font face='Verdana' size='1'>Jurusan:</font></p></td>
                            <td width='103%' style='border-style: none; border-width: medium'>
                            <font size='1' face='Verdana' color='#000080'>
                    $jurusan                      
                            </font><font size='1'>&nbsp;</font></td>
                          </tr>
                          <tr>
                  <td width='27%' style='border-style: none; border-width: medium' align='right' height='1'>
                  <p style='margin-top:1; margin-bottom:1; margin-right:10'><font face='Verdana' size='1'>Tahun 
                  Lulus:</font></p></td>
                            <td width='103%' style='border-style: none; border-width: medium'>
                            <font size='1' face='Verdana' color='#000080'>$tahunlulus</font><font size='1'>
                            </font><font size='1'>&nbsp;</font></td>
                          </tr>
                          <tr>
                  <td width='27%' style='border-style: none; border-width: medium' align='right' height='1' valign='top'>
                  <p style='margin-top:1; margin-bottom:1; margin-right:10'><font face='Verdana' size='1'>Alamat:</font></p></td>
                            <td width='103%' style='border-style: none; border-width: medium'>
                            <font size='1' face='Verdana' color='#000080'>$alamat_sma</font><font size='1'>&nbsp;
                            </font></td>
                          </tr>
                          <tr>
                  <td width='27%' style='border-style: none; border-width: medium' align='right' height='1'>
                  <p style='margin-top:1; margin-bottom:1; margin-right:10'><font face='Verdana' size='1'>Kota:</font></p></td>
                            <td width='103%' style='border-style: none; border-width: medium'>
                            <font size='1' face='Verdana' color='#000080'>$kota_sma</font><font size='1'>&nbsp;
                            </font></td>
                          </tr>
                          <tr>
                  <td width='27%' style='border-style: none; border-width: medium' align='right' height='1'>
                  <p style='margin-top:1; margin-bottom:1; margin-right:10'><font face='Verdana' size='1'>Kode Pos:</font></p></td>
                            <td width='103%' style='border-style: none; border-width: medium'>
                            <font size='1' face='Verdana' color='#000080'>$kodepos_sma</font><font size='1'>&nbsp;</font></td>
                          </tr>
                        </tbody></table>
                        </td>
                  <td width='469' style='border-style: none; border-width: medium' align='right' height='125' colspan='2' valign='top'>
                        <table border='0' cellpadding='0' cellspacing='0' style='border-collapse: collapse; border-width: 0' bordercolor='#111111' width='100%' id='AutoNumber11'>
                          <tbody>
                           <tr>
                            <td width='7%' style='border-style: none; border-width: medium' align='left'>
                            <p align='center'>
                            <font face='Wingdings' size='2'>
                                      o
                            </font></p></td>
                            <td width='94%' style='border-style: none; border-width: medium'>
                            <font face='Verdana' size='1'>Fotokopi KTP/kartu pelajar calon mahasiswa</font></td>
                          </tr>
                          
                            <tr>
                            <td width='7%' style='border-style: none; border-width: medium' align='left'>
                            <p align='center'>
                            <font face='Wingdings' size='2'>
                                      o
                            </font></p></td>
                            <td width='94%' style='border-style: none; border-width: medium'>
                            <font face='Verdana' size='1'>Fotokopi KTP orang tua</font></td>
                          </tr>
                          <tr>
                            <td width='7%' style='border-style: none; border-width: medium' align='left'>
                            <p align='center'>
                            <font face='Wingdings' size='2'>
                                      o
                            </font></p></td>
                            <td width='94%' style='border-style: none; border-width: medium'>
                            <font face='Verdana' size='1'>Fotokopi akta kelahiran</font></td>
                          </tr>
                          <tr>
                            <td width='7%' style='border-style: none; border-width: medium' align='left'>
                            <p align='center'>
                            <font face='Wingdings' size='2'>
                                      o
                            </font></p></td>
                            <td width='94%' style='border-style: none; border-width: medium'>
                            <font face='Verdana' size='1'>Fotokopi rapor legalisir semester 1 – 5</font></td>
                          </tr>
                          <tr>
                            <td width='101%' style='border-style: none; border-width: medium' colspan='2' align='left'>
                            <p align='center'>
                            <font size='2'>&nbsp;</font></p></td>
                          </tr>
                          </tbody></table>
                        </td>
                      </tr>
                      <tr>
                  <td width='963' style='border-style: none; border-width: medium' align='right' height='10' colspan='5'>
                        <font size='1'>&nbsp;</font></td>
                      </tr>
                      <tr>
                  <td width='467' style='border:1px solid #C0C0C0; ' align='right' height='18' colspan='2'>
                        <p align='center'><b><font size='2' face='Verdana'>TANDA 
                        TANGAN</font></b></p></td>
                        <td width='24' style='border-style: none; border-width: medium' height='17'></td>
                  <td width='468' style='border:1px solid #C0C0C0; ' align='right' height='18' colspan='2'>
                        <p align='center'>
                  <span style='text-transform: uppercase; font-weight: 700'>
                  <font size='2' face='Verdana'>Darimana anda mengetahui Universitas 
                              bakrie</font></span></p></td>
                      </tr>
                      <tr>
                  <td width='469' style='border-style: none; border-width: medium' align='right' height='281' colspan='2' valign='top'>
                        <table border='0' cellpadding='0' cellspacing='0' style='border-collapse: collapse; border-width: 0' bordercolor='#111111' width='100%' id='AutoNumber13'>
                          <tbody><tr>
                            <td width='100%' style='border-style: none; border-width: medium' colspan='3'>
                            <font size='1'>&nbsp;</font></td>
                          </tr>
                          <tr>
                            <td width='100%' style='border-style: none; border-width: medium' colspan='3'>
                            <p align='justify'><font size='1' face='Verdana'>Dengan 
                            ini saya menyatakan bahwa data-data yang saya berikan 
                            adalah benar adanya dan bersedia menerima sangsi apabila 
                            data tersebut tidak benar. Jika saya diterima menjadi 
                            mahasiswa UB, saya bersedia mengikuti segala peraturan 
                            yang berlaku.</font></p></td>
                          </tr>
                          <tr>
                            <td width='100%' style='border-style: none; border-width: medium' colspan='3'>&nbsp;</td>
                          </tr>
                          <tr>
                            <td width='100%' style='border-style: none; border-width: medium' colspan='3'>
                            <font face='Verdana' size='1'>Jakarta,</font></td>
                          </tr>
                          <tr>
                            <td width='30%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='44%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='26%' style='border-style: none; border-width: medium'>&nbsp;</td>
                          </tr>
                          <tr>
                            <td width='30%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='44%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='26%' style='border-style: none; border-width: medium'>&nbsp;</td>
                          </tr>
                          <tr>
                            <td width='30%' style='border-style: none; border-width: medium'>
                            <font face='Verdana' size='1'>Tanda tangan</font></td>
                            <td width='44%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='26%' style='border-style: none; border-width: medium'>&nbsp;</td>
                          </tr>
                          <tr>
                            <td width='30%' style='border-style: none; border-width: medium'>
                            <font face='Verdana' size='1'>calon mahasiswa</font></td>
                            <td width='44%' style='border-style: none; border-width: medium'>
                            <div style='border-bottom: 1px solid #C0C0C0'>
      &nbsp;</div>
                            </td>
                            <td width='26%' style='border-style: none; border-width: medium'>&nbsp;</td>
                          </tr>
                          <tr>
                            <td width='30%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='44%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='26%' style='border-style: none; border-width: medium'>&nbsp;</td>
                          </tr>
                          <tr>
                            <td width='30%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='44%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='26%' style='border-style: none; border-width: medium'>&nbsp;</td>
                          </tr>
                          <tr>
                            <td width='30%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='44%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='26%' style='border-style: none; border-width: medium'>&nbsp;</td>
                          </tr>
                          <tr>
                            <td width='30%' style='border-style: none; border-width: medium'>
                            <font face='Verdana' size='1'>Tanda tangan</font></td>
                            <td width='44%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='26%' style='border-style: none; border-width: medium'>&nbsp;</td>
                          </tr>
                          <tr>
                            <td width='30%' style='border-style: none; border-width: medium'>
                            <font face='Verdana' size='1'>Orang tua / Wali</font></td>
                            <td width='44%' style='border-style: none; border-width: medium'>
                            <div style='border-bottom: 1px solid #C0C0C0'>
      &nbsp;</div>
                            </td>
                            <td width='26%' style='border-style: none; border-width: medium'>&nbsp;</td>
                          </tr>
                          <tr>
                            <td width='30%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='44%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='26%' style='border-style: none; border-width: medium'>&nbsp;</td>
                          </tr>
                        </tbody></table>
                        </td>
                        <td width='25' style='border-style: none; border-width: medium' height='281'>&nbsp;</td>
                  <td width='469' style='border-style: none; border-width: medium' align='right' height='281' colspan='2' valign='top'>
                        <table border='0' cellpadding='0' cellspacing='0' style='border-collapse: collapse; border-width: 0' bordercolor='#111111' width='100%' id='AutoNumber12'>
                          <tbody><tr>
                            <td width='100%' style='border-style: none; border-width: medium' colspan='2'>
                            <font size='1'>&nbsp;</font></td>
                          </tr>";
            
       $info_array = array(
           "Mahasiswa yang sudah kuliah di UB",
           "Teman / Saudara",
           "Pameran Pendidikan",
            "Pameran di Sekolah",
            "Presentasi di Sekolah",
            "Brosur",
            "Koran",
            "Search Engine",
            "Web Site",
            "Lain-lain");
       
       $info_ubs = $reg_node->field_reg_sourceinfo['und'];
       $info_student = array();
       foreach($info_ubs as $info_ub){
           $info_student[] = $info_ub['value'];
       }
       
       foreach($info_array as $info){
           if(in_array($info, $info_student)){
               $sign = "&#9745;";
           }
           else{
               $sign = "o";
           }
               $output .= "
                          <tr>
                            <td width='7%' style='border-style: none; border-width: medium' align='center'>
                            <font face='Dingbats' size='2'>

                                      $sign

                            </font></td>
                    <td width='87%' style='border-style: none; border-width: medium' height='1'>
                  <font size='1' face='Verdana'>$info<font size='1' face='Verdana' color='#003399'></font></font></td>
                          </tr>";
                       
           
       }
       
       
       $output .= "
                          <tr>
                            <td width='7%' style='border-style: none; border-width: medium'>&nbsp;</td>
                            <td width='93%' style='border-style: none; border-width: medium'>&nbsp;</td>
                          </tr>
                        </tbody></table>
                        </td>
                      </tr>
                    </tbody></table>
              </td>
                    </tr>
          </tbody></table>
          </td>
        </tr>
      </tbody></table><p class=footer></p>";
   }            

    
    $output .= '</body></html>';
    
    print $output;  
}

function cetak_formulir_get_style(){
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