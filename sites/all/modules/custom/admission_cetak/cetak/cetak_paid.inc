<?php

//Cetak calon mahasiswa yang sudah bayar Ujian Masuk
function admission_cetak_paid(){
    $output = '<html><head></head>';
    $output .= '<body>';
    
    $schedule_nid = arg(2);
    
    $sch_node = node_load($schedule_nid);
    $tanggal_tes = date('d M Y', strtotime($sch_node->field_schedule_waktu['und'][0]['value']));
    $tempat_test = $sch_node->field_schedule_place['und'][0]['value'];
    $time1 = $sch_node->field_schedule_waktu['und'][0]['value'];
    $time2 = $sch_node->field_schedule_waktu['und'][0]['value2'];
    $jam1 = date('H:i', strtotime($time1));
    $jam2 = date('H:i', strtotime($time2));
    
   $query = new EntityFieldQuery();
   $query->entityCondition('entity_type', 'node')
           ->entityCondition('bundle', 'registration')
           ->propertyCondition('status', 1)         
           ->fieldCondition('field_reg_schedule', 'target_id', $schedule_nid , '=');
    $result = $query->execute();   
    
    $output .=
	"<table border='0' width='100%' cellspacing='0' cellpadding='0'>
	<tbody><tr>
		<td width='14%'>
		<span style='text-transform: uppercase; font-weight: 700'><font size='1' face='Verdana'>Tanggal Tes:</font></span></td>
		<td width='86%'><font size='1' face='Verdana'>$tanggal_tes</font></td>
	</tr>
	<tr>
		<td width='14%'>
		<span style='text-transform: uppercase; font-weight: 700'><font size='1' face='Verdana'>Jam:</font></span></td>
		<td width='86%'><font size='1' face='Verdana'>$jam1 s/d $jam2 </font></td>
	</tr>
	<tr>
		<td width='14%'>
		<span style='text-transform: uppercase; font-weight: 700'><font size='1' face='Verdana'>Tempat:</font></span></td>
		<td width='86%'><font size='1' face='Verdana'>$tempat_test                                                                                               - Pekanbaru                     </font></td>
	</tr>
	<tr>
		<td width='14%'>&nbsp;</td>
		<td width='86%'>&nbsp;</td>
	</tr>
	<tr>
            <td colspan='2'>
            <table border='0' width='100%' cellspacing='0' cellpadding='0'>
                <tbody><tr>
                        <td style='border:1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px' width='43' bgcolor='#C0C0C0'>
                        <p style='margin-top: 2px; margin-bottom: 2px'>
                        <b><font size='1' face='Verdana'>NO</font></b></p></td>
                        <td style='border-bottom:1px solid #000000; border-left-color: #000000; border-right: 1px solid #000000; border-top: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px' bgcolor='#C0C0C0'>
                        <p style='margin-top: 2px; margin-bottom: 2px'>
                        <b><font face='Verdana' size='1'>REG</font></b></p></td>
                        <td style='border-bottom:1px solid #000000; border-left-color: #000000; border-right: 1px solid #000000; border-top: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px' bgcolor='#C0C0C0'>
                        <b><font size='1' face='Verdana'>B/R</font></b></td>
                        <td style='border-bottom:1px solid #000000; border-left-color: #000000; border-right: 1px solid #000000; border-top: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px' bgcolor='#C0C0C0'>
                        <b><font size='1' face='Verdana'>PD</font></b></td>
                        <td style='border-bottom:1px solid #000000; border-left-color: #000000; border-right: 1px solid #000000; border-top: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px' bgcolor='#C0C0C0'>
                        <b><font size='1' face='Verdana'>JR</font></b></td>
                        <td style='border-bottom:1px solid #000000; border-left-color: #000000; border-right: 1px solid #000000; border-top: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px' bgcolor='#C0C0C0'>
                        <p style='margin-top: 2px; margin-bottom: 2px'>
                        <b><font size='1' face='Verdana'>NAMA</font></b></p></td>
                        <td style='border-bottom:1px solid #000000; border-left-color: #000000; border-right: 1px solid #000000; border-top: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px' bgcolor='#C0C0C0'>
                        <b><font size='1' face='Verdana'>SMA</font></b></td>
                        <td style='border-bottom:1px solid #000000; border-left-color: #000000; border-right: 1px solid #000000; border-top: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px' bgcolor='#C0C0C0'>
                        <b><font size='1' face='Verdana'>KOTA</font></b></td>
                        <td style='border-bottom:1px solid #000000; border-left-color: #000000; border-right: 1px solid #000000; border-top: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px' bgcolor='#C0C0C0'>
                        <p style='margin-top: 2px; margin-bottom: 2px'>
                        <b><font size='1' face='Verdana'>TELEPON</font></b></p></td>
                        <td style='border-bottom:1px solid #000000; border-left-color: #000000; border-right: 1px solid #000000; border-top: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px' bgcolor='#C0C0C0'>
                        <p style='margin-top: 2px; margin-bottom: 2px'>
                        <b><font size='1' face='Verdana'>HP</font></b></p></td>
                        <td style='border-bottom:1px solid #000000; border-left-color: #000000; border-right: 1px solid #000000; border-top: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px' bgcolor='#C0C0C0'>
                        <p style='margin-top: 2px; margin-bottom: 2px'>
                        <b><font size='1' face='Verdana'>TGL DAFTAR</font></b></p></td>
                        <td style='border-bottom:1px solid #000000; border-left-color: #000000; border-right: 1px solid #000000; border-top: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px' bgcolor='#C0C0C0'>
                        <b><font size='1' face='Verdana'>DOKUMEN</font></b></td>
                </tr>";
			
    $no = 0;
    if($result['node']){
        $prodi1 = array();
//        $prodi2 = array();
//        $prodi3 = array();
        $jurusan_array = array();
      foreach(element_children($result['node']) as $reg_nid){
        $reg_node = node_load($reg_nid);

        if($reg_node->field_reg_fee['und'][0]['value'] == 'Paid'){
         $no++;
         $no_reg = $reg_node->field_reg_no['und'][0]['value'];
         $prodi_node = node_load($reg_node->field_reg_departement1['und'][0]['target_id']);
         $prodi_pilihan = $prodi_node->title;
         
         $profile = profile2_load_by_user($reg_node->uid);
         $nama = $profile['data_pribadi']->field_personal_fullname['und'][0]['value'];
         $tipe_sekolah = $profile['data_sekolah']->field_sekolah_tipe['und'][0]['value'];
         $nama_sekolah = $profile['data_sekolah']->field_sekolah_sma['und'][0]['value'];
         $asal_sekolah = $tipe_sekolah.' '.$nama_sekolah;
         
         $items = field_get_items('profile2', $profile['data_pribadi'], 'field_personal_address');
        foreach($items as $item){
            $fc = field_collection_field_get_entity($item);          
            $kota_node = node_load($fc->field_address_kota['und'][0]['target_id']);
            $kota = $kota_node->title;
        }
         $telp = $profile['data_pribadi']->field_personal_telp['und'][0]['value'];
         $hp = $profile['data_pribadi']->field_personal_hp['und'][0]['value'];
         $tanggal_daftar = date('d M Y',  $reg_node->created);
         
         //cek kelengkapan dokumen
         include drupal_get_path('module', 'admission_user').'/admission_user.api.inc';
         $cek_dok = admission_user_cek_syarat($reg_node->uid, 'usm'); 
         
         $is_lengkap = ($cek_dok)? 'Lengkap':'Belum Lengkap';
                
         $jurusan_sekolah = $profile['data_sekolah']->field_sekolah_jurusan['und'][0]['value'];
         $jurusan_array[] = $jurusan_sekolah;
         
         $pilihan1 = $reg_node->field_reg_departement1['und'][0]['target_id'];
//         $pilihan2 = $reg_node->field_reg_departement2['und'][0]['target_id'];
//         $pilihan3 = $reg_node->field_reg_departement3['und'][0]['target_id'];
         
         $prodi1[] = $pilihan1;
//         $prodi2[] = $pilihan2;
//         $prodi3[] = $pilihan3;                  
         
         $output .=	
            "<tr>
                    <td style='border-left:1px solid #000000; border-right:1px solid #000000; border-bottom:1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px; border-top-color:#000000' width='43'>
                    <font size='1' face='Verdana'>$no</font></td>
                    <td style='border-left-color: #000000; border-right: 1px solid #000000; border-bottom: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px; border-top-color:#000000'>
                    <font size='1' face='Verdana'>$no_reg</font></td>
                    <td style='border-left-color: #000000; border-right: 1px solid #000000; border-bottom: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px; border-top-color:#000000'>
                    <font size='1' face='Verdana'>
                    R</font></td>
                    <td style='border-left-color: #000000; border-right: 1px solid #000000; border-bottom: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px; border-top-color:#000000'>
                    <font size='1' face='Verdana'>$prodi_pilihan</font></td>


                    <td style='border-left-color: #000000; border-right: 1px solid #000000; border-bottom: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px; border-top-color:#000000'>
                    <font face='Verdana' style='font-size: 8pt'>
                    1                                                  				
                    </font></td>
                    <td style='border-left-color: #000000; border-right: 1px solid #000000; border-bottom: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px; border-top-color:#000000'>
                    <font size='1' face='Verdana'>$nama</font></td>
                    <td style='border-left-color: #000000; border-right: 1px solid #000000; border-bottom: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px; border-top-color:#000000'>
                    <font size='1' face='Verdana'>$asal_sekolah</font></td>
                    <td style='border-left-color: #000000; border-right: 1px solid #000000; border-bottom: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px; border-top-color:#000000'>
                    <font face='verdana' size='1'>$kota</font></td>
                    <td style='border-left-color: #000000; border-right: 1px solid #000000; border-bottom: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px; border-top-color:#000000'>
                    <font face='Verdana' size='1'>$telp</font></td>
                    <td style='border-left-color: #000000; border-right: 1px solid #000000; border-bottom: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px; border-top-color:#000000'>
                    <font size='1' face='Verdana'>$hp</font></td>
                    <td style='border-left-color: #000000; border-right: 1px solid #000000; border-bottom: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px; border-top-color:#000000'>
                    <font size='1' face='Verdana'>$tanggal_daftar</font></td>
                    <td style='border-left-color: #000000; border-right: 1px solid #000000; border-bottom: 1px solid #000000; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px; border-top-color:#000000'>
                    <font size='1' face='Verdana'>
                    $is_lengkap
                    </font></td>
            </tr>";
       }
      }
      
     $ps1 = array_count_values($prodi1);
//     $ps2 = array_count_values($prodi2);
//     $ps3 = array_count_values($prodi3);
     
     $jurusan = array_count_values($jurusan_array);
    }
		
        $output .=
		"</tbody></table>
		</td>
	</tr>
</tbody></table>";
    
         $output .= 
            "<table border='0' width='30%' cellspacing='0' cellpadding='0'>
	<tbody><tr>
		<td>&nbsp;</td>
	</tr>
	<tr>
		<td><b><font size='1' face='Verdana'><u>Pilihan Prodi</u></font></b></td>
                <td><b><font size='1' face='Verdana'></font></b></td>";
//                <td><b><font size='1' face='Verdana'><u>ke-2</u></font></b></td>
//                <td><b><font size='1' face='Verdana'><u>ke-3</u></font></b></td>
	$output .= "</tr><td><b><font size='1' face='
	<tr>
		<td><font size='1'>&nbsp;</font></td>
	</tr>";
    $prodi_array = node_load_multiple(array(),array('type' => 'departement'));
    $i = 1;
    foreach($prodi_array as $prodi){
        $nama_prodi = $prodi->field_departement_name['und'][0]['value'];
        $total_candidate = isset($ps1[$prodi->nid])?$ps1[$prodi->nid]:0;
        if($i%2){
           $output .="<tr bgcolor='#C0C0C0'>
                    <td width=60%><font size='1' face='Verdana'>$i. $nama_prodi</font></td>
                    <td width=10px><b><font size='1' face='Verdana'>{$total_candidate}</font></b></td>";
//                    <td width=10px><b><font size='1' face='Verdana'>{$ps2[$prodi->nid]}</font></b></td>
//                    <td width=10px><b><font size='1' face='Verdana'>{$ps3[$prodi->nid]}</font></b></td>
            $output .="</tr>"; 
        }
        else{
           $output .="<tr>
                    <td width=60%><font size='1' face='Verdana'>$i. $nama_prodi</font></td>
                    <td width=10px><b><font size='1' face='Verdana'>{$total_candidate}</font></b></td>";
//                    <td width=10px><b><font size='1' face='Verdana'>{$ps2[$prodi->nid]}</font></b></td>
//                    <td width=10px><b><font size='1' face='Verdana'>{$ps3[$prodi->nid]}</font></b></td>
            $output .="</tr>"; 

        }
        
        $i++;
    }
   
	$total_jurusan_ips = isset($jurusan['ips'])?$jurusan['ips']:0;
        $total_jurusan_ipa = isset($jurusan['ipa'])?$jurusan['ipa']:0;
        $total_jurusan_bahasa = isset($jurusan['bahasa'])?$jurusan['bahasa']:0;
        $total_jurusan_lain = isset($jurusan['lain'])?$jurusan['lain']:0;
        
	$output .= 
            "<tr>
		<td>&nbsp;</td>
            </tr>
	
            <tr>
                    <td><font face='Verdana' size='1'>Total peserta IPS = {$total_jurusan_ips}</font></td>
            </tr>

            <tr>
                    <td><font face='Verdana' size='1'>Total peserta IPA = {$total_jurusan_ipa}</font></td>
            </tr>
            <tr>
                    <td><font face='Verdana' size='1'>Total peserta Bahasa = {$total_jurusan_bahasa}</font></td>
            </tr>
            <tr>
                    <td><font face='Verdana' size='1'>Total peserta Lain = {$total_jurusan_lain}</font></td>
            </tr>

            <tr>
                    <td>&nbsp;</td>
            </tr>
            

            <tr>
                    <td>&nbsp;</td>
            </tr>
    </tbody></table>";
    
    $output .= '</body></html><br/>';
    
    $link_export = l('Export to Excel', "export-list-paid/$schedule_nid");
    $output .= "$link_export";
    
    return $output;
}

