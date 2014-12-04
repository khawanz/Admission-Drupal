<?php

function admission_cetak_cover(){
    global $base_path;
    global $user;
    $username = $user->name;

    $reg_nid = (int)abs(arg(2));
    $reg_node = node_load($reg_nid);
    $user_id = $reg_node->field_reg_candidate['und'][0]['target_id'];
    
//   $query = new EntityFieldQuery();
//   $query->entityCondition('entity_type', 'node')
//           ->entityCondition('bundle', 'registration')
//           ->propertyCondition('status', 1)         
//           ->fieldCondition('field_reg_candidate', 'target_id', $user_id , '=');
//   $result = $query->execute();
   
   //validation
   if(!isset($reg_node)){
       return '<strong>Belum Terdaftar.</strong>';
   }
     
   $profile = profile2_load_by_user($user_id);
    $nama = $profile['data_pribadi']->field_personal_fullname['und'][0]['value'];
//    $lahir1 = $profile['data_pribadi']->field_personal_birthdate['und'][0]['value'];
//    $lahir = date('d M Y', strtotime($lahir1));
      
    $noreg = $reg_node->field_reg_no['und'][0]['value'];
    $nomor_file = isset($reg_node->field_reg_fileno['und'][0]['value'])?
            $reg_node->field_reg_fileno['und'][0]['value']:'-';
    
    $jurusan_node = node_load($reg_node->field_reg_departement1['und'][0]['target_id']);
    $jurusan = $jurusan_node->title;
    
    $sched_node = node_load($reg_node->field_reg_schedule['und'][0]['target_id']);
    $gelombang = $sched_node->field_schedule_gelombang['und'][0]['value'];
    $kota = $sched_node->field_schedule_city['und'][0]['value'];
    
    $user_load = user_load($user_id);
    $foto = theme('user_picture', array('account' => $user_load));
    
   $output = '<html><head><title>Print Cover</title>';
   $output .= cetak_cover_get_style();
   $output .= '</head><body>';

   $path_gif = $base_path.'sites/default/files/logo_UB.gif';

   $output .= '<center><button class=noprint type=button onclick=window.print()>Print</button></center>';
    
    $output .= "<table border='0' width='100%' cellspacing='0' cellpadding='0' style='border: 1px solid #000000'>
			<tbody><tr>
				<td>
                                <p align='center'>
				<b>Gelombang $gelombang $kota</b></p></td>
			</tr>
			<tr>
				<td>
				<p align='center'>
				<img border='0' src=$path_gif width='300' height='34'></p></td>
			</tr>
			<tr>
				<td>
				&nbsp;</td>
			</tr>
			<tr>
				<td>
				<p align='center'><b><u><font size='4'>COVER SHEET - APPLICATION FOR ADMISSION</font></u></b></p></td>
			</tr>
			<tr>
				<td height='39'>
				&nbsp;</td>
			</tr>
			<tr>
				<td>
				<div align='center'>
					<table border='0' width='95%' cellspacing='0' cellpadding='0'>
						<tbody>
                                                <tr>
							<td width='193'>
							<p style='margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'><b>Nomor File</font></p></td>
							<td width='200px'>
							<p style='margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'>:  $nomor_file </b></font></p></td>
                                                            <td rowspan=6><p align=left>$foto</p></td>
						</tr>
                                                <tr>
							<td width='193'>
							<p style='margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'>Nomor Aplikasi</font></p></td>
							<td>
							<p style='margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'>:  $noreg </font></p></td>
						</tr>
						<tr>
							<td width='193'>
							<p style='margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'>Nama</font></p></td>
							<td>
							<p style='margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'>: $nama</font></p></td>
						</tr>
						<tr>
							<td width='193'>
							<p style='margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'>Jurusan</font></p></td>
							<td>
							<p style='margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'>: $jurusan    </font></p></td>
						</tr>
						<tr>
							<td width='193'>
							<p style='margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'>Diproses Tanggal</font></p></td>
							<td>
							<p style='margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'>: 13 October 2014</font></p></td>
						</tr>
						<tr>
							<td width='193'>
							<p style='margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'>Diproses Oleh</font></p></td>
							<td>
							<p style='margin-top: 5px; margin-bottom: 5px'>
							<font size='2' face='Verdana'>: $username</font></p></td>
						</tr>
						<tr>
							<td width='193' style='border-bottom:1px solid #C0C0C0; '>&nbsp;</td>
							<td style='border-bottom:1px solid #C0C0C0; '>&nbsp;</td>
						</tr>
						<tr>
							<td width='193' style='border-bottom-style: none; border-bottom-width: medium'>&nbsp;</td>
							<td style='border-bottom-style: none; border-bottom-width: medium'>&nbsp;</td>
						</tr>";
    
                                                  
    //apakah sudah bayar
    $is_paid = ($reg_node->field_reg_fee['und'][0]['value'] == 'Paid')? "&#9745;":"o";
    $is_not_paid = ($reg_node->field_reg_fee['und'][0]['value'] == 'Not Yet')? "&#9745;":"o";
                                              $output .=
						"<tr>
							<td width='193' style='border-top-style: none; border-top-width: medium'>
							<font size='2' face='Verdana'>APPLICATION FEE</font></td>
							<td style='border-top-style: none; border-top-width: medium'>
							: <font face='Wingdings'>$is_not_paid</font><font face='Verdana' size='2'> 
							Free &nbsp;&nbsp;&nbsp;&nbsp; </font>
							<font face='Wingdings'>$is_paid</font><font face='Verdana' size='2'> 
							Paid &nbsp;&nbsp;&nbsp;&nbsp; </font>
							</td>
						</tr>";
                                              
                                              $output .=
						"<tr>
							<td width='193' style='border-bottom:1px solid #C0C0C0; border-top-width: medium; '>&nbsp;</td>
							<td style='border-bottom:1px solid #C0C0C0; border-top-width: medium; '>&nbsp;</td>
						</tr>
						<tr>
							<td width='193'>&nbsp;</td>
							<td>&nbsp;</td>
						</tr>
						
						
						<tr>
							<td width='193'>&nbsp;</td>
							<td>&nbsp;</td>
						</tr>
						<tr>
							<td width='193'><font size='2' face='Verdana'>
							DOCUMENT CHECK LIST</font></td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='1'>
							</font><font face='Verdana' size='2'>Bukti Pembayaran Pendaftaran USM</font></p></td>
						</tr>
						<tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Formulir Pendaftaran</font></p></td>
						</tr>
						<tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Fotokopi Akte Kelahiran</font></p></td>
						</tr>";
						
                     $cek_foto = empty($foto)? "o":"&#9745;";                    
                                              $output .=
						"<tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Pas Foto 3x4 (warna) &nbsp;&nbsp;
                                                        <strong><font face='Wingdings'>$cek_foto</font></strong>&nbsp;Upload</font></p></td>
						</tr>";
                                                
                                              $output .=
						"<tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Fotokopi Identitas Diri KTP/SIM/Kartu Pelajar, dll</font></p></td>
						</tr>
                                                <tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Fotokopi Identitas Orang Tua/Wali KTP, dll</font></p></td>
						</tr>
                                                <tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Surat Pernyataan Mahasiswa Baru</font></p></td>
						</tr>
                                                <tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Fotokopi Surat Keterangan Catatan Kepolisian (SKCK)</font></p></td>
						</tr>
                                                <tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Surat Keterangan Bebas Narkoba</font></p></td>
						</tr>
                                                <tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Surat Keterangan Sehat dari Puskesmas/Rumah Sakit</font></p></td>
						</tr>
                                                <tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Surat Keterangan Tidak Buta Warna dari Puskesmas/Rumah Sakit</font></p></td>
						</tr>
                                                <tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Fotokopi Kartu Keluarga</font></p></td>
						</tr>
                                                <tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Fotokopi Ijazah Legalisir</font></p></td>
						</tr>
                                                <tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Fotokopi SKHUN Legalisir</font></p></td>
						</tr>
                                                <tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Fotokopi Rapor Legalisir</font></p></td>
						</tr>
                                                <tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Lembar Bukti Pembayaran Registrasi Ulang &nbsp;&nbsp;
                                                        <strong><font face='Wingdings'>o</font></strong>&nbsp;Lunas</font></p></td>
						</tr>
                                                <tr>
							<td width='193'>&nbsp;</td>
							<td>
							<p style='margin-left: 5px; margin-top:5px; margin-bottom:5px'><font face='Wingdings'>o</font><font face='Verdana' size='2'> 
							Dokumen Lain:</font></p></td>
						</tr>
						<tr>
							<td width='193'>&nbsp;</td>
							<td>
							<table border='0' width='100%' cellspacing='0' cellpadding='0'>
								<tbody><tr>
									<td width='26'>&nbsp;</td>
									<td style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
								<tr>
									<td width='26'>&nbsp;</td>
									<td style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
								<tr>
									<td width='26'>&nbsp;</td>
									<td style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
								<tr>
									<td width='26'>&nbsp;</td>
									<td style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
								<tr>
									<td width='26'>&nbsp;</td>
									<td style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
							</tbody></table>
							</td>
						</tr>
						<tr>
							<td width='193' style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
							<td style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
						</tr>
						<tr>
							<td width='193'>&nbsp;</td>
							<td>&nbsp;</td>
						</tr>
						<tr>
							<td width='193' valign='top'>
							<font size='2' face='Verdana'>Application Status</font></td>
							<td>
							<table border='0' width='100%' cellspacing='0' cellpadding='0'>
								<tbody><tr>
									<td width='27'>&nbsp;</td>
									<td style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
								<tr>
									<td width='27'>&nbsp;</td>
									<td style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
								<tr>
									<td width='27'>&nbsp;</td>
									<td style='border-left-style: solid; border-left-width: 0; border-right-style: solid; border-right-width: 0; border-top-style: solid; border-top-width: 0; border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
								<tr>
									<td width='27'>&nbsp;</td>
									<td style='border-left-style: solid; border-left-width: 0; border-right-style: solid; border-right-width: 0; border-top-style: solid; border-top-width: 0; border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
								<tr>
									<td width='27'>&nbsp;</td>
									<td style='border-left-style: solid; border-left-width: 0; border-right-style: solid; border-right-width: 0; border-top-style: solid; border-top-width: 0; border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
							</tbody></table>
							</td>
						</tr>
                                                <tr>
							<td width='193' style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
							<td style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
						</tr>
						<tr>
							<td width='193'>&nbsp;</td>
							<td>&nbsp;</td>
						</tr>
                                                <tr>
							<td width='193' valign='top'>
							<font size='2' face='Verdana'>Note</font></td>
							<td>
							<table border='0' width='100%' cellspacing='0' cellpadding='0'>
								<tbody><tr>
									<td width='27'>&nbsp;</td>
									<td style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
								<tr>
									<td width='27'>&nbsp;</td>
									<td style='border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
								<tr>
									<td width='27'>&nbsp;</td>
									<td style='border-left-style: solid; border-left-width: 0; border-right-style: solid; border-right-width: 0; border-top-style: solid; border-top-width: 0; border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
								<tr>
									<td width='27'>&nbsp;</td>
									<td style='border-left-style: solid; border-left-width: 0; border-right-style: solid; border-right-width: 0; border-top-style: solid; border-top-width: 0; border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
								<tr>
									<td width='27'>&nbsp;</td>
									<td style='border-left-style: solid; border-left-width: 0; border-right-style: solid; border-right-width: 0; border-top-style: solid; border-top-width: 0; border-bottom: 1px solid #C0C0C0'>&nbsp;</td>
								</tr>
							</tbody></table>
							</td>
						</tr>
					</tbody></table>
				</div>
				</td>
			</tr>
			<tr>
				<td>
				&nbsp;</td>
			</tr>
		</tbody></table>";
    
    print $output;
}

function cetak_cover_get_style(){
     $style = '<style>
             @media print{
             .noprint{
               display:none
              }
             }
             </style>';
    
    return $style;
}