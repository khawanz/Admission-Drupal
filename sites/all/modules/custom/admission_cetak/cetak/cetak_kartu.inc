<?php
function admission_cetak_kartu(){
    //global $user;
    global $base_path;  
       
    
    $reg_nid = (int)abs(arg(2));
    $reg_node = node_load($reg_nid);
    $user_id = $reg_node->field_reg_candidate['und'][0]['target_id'];
    $biaya = strtolower($reg_node->field_reg_fee['und'][0]['value']);
    
    //$current_user = user_load($user_id);
    
//   $query = new EntityFieldQuery();
//   $query->entityCondition('entity_type', 'node')
//           ->entityCondition('bundle', 'registration')
//           ->propertyCondition('status', 1)         
//           ->fieldCondition('field_reg_candidate', 'target_id', $user_id , '=');
//   $result = $query->execute();
   
   //validation
   if(empty($reg_node)){
       return 'PAGE NOT FOUND';
   }
   
   //jika registrasi belum dibayar atau tidak gratis maka tampil pesan error
   if($biaya != 'paid' AND $biaya != 'free'){
       return 'Registrasi ini belum dibayar.';
   }
   
    $profile = profile2_load_by_user($user_id);
   
   $nama = $profile['data_pribadi']->field_personal_fullname['und'][0]['value'];
   //$tempat_lahir = $profile['data_pribadi']->field_personal_birthplace['und'][0]['value'];
   $tanggal_lahir = $profile['data_pribadi']->field_personal_birthdate['und'][0]['value'];
   $tgl_lahir_text = date('d M Y', strtotime($tanggal_lahir));
   
   $user_load = user_load($user_id);
    $foto = theme('user_picture', array('account' => $user_load));
    
   $sekolah =  $profile['data_sekolah']->field_sekolah_tipe['und'][0]['value'];
   $nama_sekolah = $profile['data_sekolah']->field_sekolah_sma['und'][0]['value'];
   
   //$reg_node = node_load(key($result['node']));
   $noreg = $reg_node->field_reg_no['und'][0]['value'];
   
   $sched_node = node_load($reg_node->field_reg_schedule['und'][0]['target_id']); 
   $gelombang = $sched_node->field_schedule_gelombang['und'][0]['value'];
   $waktu1 = $sched_node->field_schedule_waktu['und'][0]['value'];
   $waktu1 = date('d M Y H:i', strtotime($waktu1));
   $waktu2 = $sched_node->field_schedule_waktu['und'][0]['value2'];
   $waktu2 = date('H:i', strtotime($waktu2));
   $tempat = $sched_node->field_schedule_place['und'][0]['value'];
   $alamat = $sched_node->field_schedule_address['und'][0]['value'];
   $kota = $sched_node->field_schedule_city['und'][0]['value'];
   
   $output = '<html><head><title>Print Formulir Pendaftaran</title>';
   $output .= cetak_formulir_get_style();
   $output .= '</head><body>';
   
    $path_gif = $base_path.'sites/default/files/logo_UB.gif';
    
     $output .= '<center><button class=noprint type=button onclick=window.print()>Print</button></center>';
     
    $output .= "<table border='0' width='100%' cellspacing='0' cellpadding='0' style='border: 1px solid #000000'>
			<tbody><tr>
				<td>
				<table border='0' width='100%' cellspacing='0' cellpadding='0'>
					<tbody><tr>
						<td width='74%'>
				&nbsp;</td>
						<td rowspan='7' width='25%' valign='top'>
						<p align='right'>
						
						</p></td>
						<td width='1%'>&nbsp;</td>
					</tr>
					<tr>
						<td width='74%'>
				<p style='margin-left: 10px'>
				<img border='0' src='$path_gif' width='150' height='42'></p></td>
						<td width='1%'>&nbsp;</td>
					</tr>
					<tr>
						<td width='74%'>
						&nbsp;</td>
						<td width='1%'>&nbsp;</td>
					</tr>
					<tr>
						<td width='74%'>
						<p align='left' style='margin-left: 10px'>
						<font face='Calibri' size='4'>TANDA PESERTA USM-UB</font></p></td>
						<td width='1%'>&nbsp;</td>
					</tr>
					<tr>
						<td width='74%'>&nbsp;</td>
						<td width='1%'>&nbsp;</td>
					</tr>
					<tr>
						<td width='74%'>
						<table border='0' width='100%' cellspacing='0' cellpadding='0' style='border-right-width: 0px; border-top-width: 0px'>
							<tbody><tr>
								<td width='185' style='border-right: medium none #C0C0C0; border-top: medium none #C0C0C0; border-bottom: 1px solid #C0C0C0'>
								<p style='margin-left: 10px; margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'>NAMA LENGKAP:</font></p></td>
								<td style='border-left-style: none; border-left-width: medium; border-right: medium none #C0C0C0; border-top: medium none #C0C0C0; border-bottom: 1px solid #C0C0C0'>
								<font face='Verdana' size='2'>$nama</font></td>
                                                                    <td rowspan = 4>$foto</td>
							</tr>
							<tr>
								<td width='185' style='border-right: medium none #C0C0C0; border-bottom: 1px solid #C0C0C0'>
								<p style='margin-left: 10px; margin-top: 5px; margin-bottom: 5px'>
							<font face='Verdana' size='2'>TANGGAL LAHIR:</font></p></td>
								<td style='border-left-style: none; border-left-width: medium; border-right: medium none #C0C0C0; border-bottom: 1px solid #C0C0C0'>
								<font face='Verdana' size='2'>$tgl_lahir_text</font></td>
							</tr>
							<tr>
								<td width='185' style='border-bottom: 1px solid #C0C0C0'>
								<p style='margin-left: 10px; margin-top: 5px; margin-bottom: 5px'>
								<font size='2' face='Verdana'>ASAL SEKOLAH:</font></p></td>
								<td style='border-bottom: 1px solid #C0C0C0'>
								<font size='2' face='Verdana'>$sekolah $nama_sekolah </font></td>
							</tr>
							<tr>
								<td width='185' style='border-bottom: 1px solid #C0C0C0'>
								<p style='margin-left: 10px; margin-top: 5px; margin-bottom: 5px'>
								<font size='2' face='Verdana'>NO. PENDAFTARAN:</font></p></td>
								<td style='border-bottom: 1px solid #C0C0C0'>
								<font face='Verdana' size='2'>$noreg</font></td>
							</tr>
						</tbody></table>
						</td>
						<td width='1%'>&nbsp;</td>
					</tr>
					<tr>
						<td width='74%'>&nbsp;</td>
						<td width='1%'>&nbsp;</td>
					</tr>
					<tr>
						<td colspan='2'>
						<p style='margin-left: 10px; margin-top:2px; margin-bottom:2px'>
				<font size='1' face='Verdana'>Nomor Aplikasi ini digunakan juga 
				sebagai nomor test Anda. Mohon dicatat dan di simpan dengan baik 
				untuk keperluan proses Anda selanjutnya. </font></p></td>
						<td width='1%'><font size='1'>&nbsp;</font></td>
					</tr>
					<tr>
						<td width='99%' colspan='2'>
						<p style='margin-left: 10px; margin-top: 2px; margin-bottom: 2px'>
						<font size='1' face='Verdana'>Peralatan yang wajib di 
						bawa pada saat tes: Bolpoin, Pensil 2B, Penghapus, Rautan Pensil, 
						Clipboard (papan jalan).</font></p></td>
						<td width='1%'><font size='1'>&nbsp;</font></td>
					</tr>
					<tr>
						<td width='99%' colspan='2'>
						<p style='margin-left: 10px'>
						<font face='Verdana' size='1'>Harap dibawa pada saat 
						mengikuti ujian dan daftar ulang apabila Anda lolos 
						seleksi.</font></p></td>
						<td width='1%'>&nbsp;</td>
					</tr>
					<tr>
						<td width='99%' colspan='2'>
						<p style='margin-left: 10px'>
						<font size='1' face='Verdana'>Berpakaian rapi dan sopan</font></p></td>
						<td width='1%'>&nbsp;</td>
					</tr>
					<tr>
						<td width='74%'>&nbsp;</td>
						<td width='25%'>&nbsp;</td>
						<td width='1%'>&nbsp;</td>
					</tr>
					<tr>
						<td width='99%' colspan='2'>
						<div align='center'>
						<table border='0' width='98%' cellspacing='0' cellpadding='0' style='border-width:0px; '>
							<tbody><tr>
								<td width='36%' style='border-left: medium none #C0C0C0; border-right: medium none #C0C0C0; border-top-style: none; border-top-width: medium; border-bottom: medium none #C0C0C0; ' valign='top'>
								<b><font size='2' face='Verdana'>MATERI TES</font></b></td>
								<td width='63%' style='border-left: medium none #C0C0C0; border-right: medium none #C0C0C0; border-top-style: none; border-top-width: medium; border-bottom: medium none #C0C0C0; ' valign='top'>
								<font face='Verdana' size='2'><b>WAKTU DAN 
								TEMPAT TEST</b></font></td>
							</tr>
							<tr>
								<td width='36%' style='border-left: medium none #C0C0C0; border-right: medium none #C0C0C0; border-top-style: none; border-top-width: medium; border-bottom: medium none #C0C0C0; ' valign='top'>
								<table border='0' width='100%' cellspacing='0' cellpadding='0'>
									<tbody><tr>
										<td style='margin:5 0; '>
										<p style='margin-left: 5px'>
										<font size='1' face='Verdana'>1. Bahasa 
										Inggris dan Matematika</font></p></td>
									</tr>
									<tr>
										<td style='margin:5 0; '>
										<p style='margin-left: 5px'>
										<font size='1' face='Verdana'>2. 
										IPA Terpadu / IPS Terpadu</font></p></td>
									</tr>
								</tbody></table>
								</td>
								<td width='63%' style='border-left: medium none #C0C0C0; border-right: medium none #C0C0C0; border-top-style: none; border-top-width: medium; border-bottom: medium none #C0C0C0; ' valign='top'>
								<table border='0' width='100%' cellspacing='0' cellpadding='0'>
									<tbody><tr>
										<td><font size='1' face='Verdana'>
										Gelombang $gelombang, $waktu1 s/d $waktu2
										</font></td>
									</tr>
									<tr>
										<td><font size='1' face='Verdana'>
										$tempat                                                                                            
										</font></td>
									</tr>
									<tr>
										<td><font size='1' face='Verdana'>
										$alamat                                                                                                                                                                                                                                          
										</font></td>
									</tr>
									<tr>
										<td><font size='1' face='Verdana'>
										$kota                      
										</font></td>
									</tr>
								</tbody></table>
								</td>
							</tr>
							</tbody></table>
						</div>
						</td>
						<td width='1%'>&nbsp;</td>
					</tr>
					<tr>
						<td width='74%'>&nbsp;</td>
						<td width='25%'>&nbsp;</td>
						<td width='1%'>&nbsp;</td>
					</tr>
				</tbody></table>
				</td>
			</tr>
		</tbody></table>";
       
    return $output;
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
