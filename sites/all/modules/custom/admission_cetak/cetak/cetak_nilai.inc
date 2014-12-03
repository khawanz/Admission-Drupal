<?php

function admission_cetak_nilai(){
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
        drupal_set_message('Silakan lakukan pendaftaran dengan mengikuti ujian masuk atau seleksi melalui jalur khusus (rapor/UN).');
       return '';
   }
    $output = '<html><head><title>Print Daftar Nilai</title>';
    $output .= cetak_nilai_get_style();
    $output .= '</head><body>';
    
    $path_gif = $base_path.'sites/default/files/logo_UB.gif';
    
    $output .= '<center><button class=noprint type=button onclick=window.print()>Print</button></center>';
    
    $profile = profile2_load_by_user($user_id);
   
   $reg_node = node_load(key($result['node']));
   $noreg = $reg_node->field_reg_no['und'][0]['value'];
   $pilihan_prodi_node = node_load($reg_node->field_reg_departement1['und'][0]['target_id']);
   $nama = $profile['data_pribadi']->field_personal_fullname['und'][0]['value'];
   $tipe_sekolah = $profile['data_sekolah']->field_sekolah_tipe['und'][0]['value'];
   $nama_sekolah = $profile['data_sekolah']->field_sekolah_sma['und'][0]['value'];
   $kota_sekolah_node = node_load($profile['data_sekolah']->field_sekolah_kota['und'][0]['target_id']);
   $sekolah = $tipe_sekolah.' '.$nama_sekolah.', '.$kota_sekolah_node->title;
   $nilai_un = isset($profile['nilai_un']->field_nilai_un_murni['und'][0]['value'])?
            $profile['nilai_un']->field_nilai_un_murni['und'][0]['value']:0;
   
    $output .= "<table border='1' cellpadding='0' cellspacing='0' style='border-collapse: collapse; border-width: 0' bordercolor='#111111' width='100%' id='AutoNumber6'>
      <tbody><tr>
        <td width='47%' style='border-style: none; border-width: medium' colspan='5'>
              <img border='0' src='$path_gif' width='300' height='34'></td>
        <td width='53%' style='border-style: none; border-width: medium' rowspan='10' align='right' valign='top' colspan='3'>
        <i>
        <font size='1' face='Verdana'>
        
        
        </font></i></td>
      </tr>
      <tr>
        <td width='47%' style='border-style: none; border-width: medium' colspan='5'>
		<font size='1'>&nbsp;</font></td>
      </tr>
      <tr>
        <td width='47%' style='border-style: none; border-width: medium' colspan='5' height='17'>
              <font face='Verdana' size='2'>DAFTAR NILAI CALON MAHASISWA BARU</font></td>
      </tr>
      <tr>
        <td width='18%' style='border-style: none; border-width: medium'>&nbsp;</td>
        <td width='51%' style='border-style: none; border-width: medium' colspan='4'>&nbsp;</td>
      </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='10'>
              <p style='margin-right:10; margin-top:1; margin-bottom:1' align='right'>
				<b>
				<font face='Verdana' size='1'>Nomor Registrasi:</font></b></p></td>
              <td width='51%' style='border-style: none; border-width: medium' colspan='4'>
              <font size='1' face='Verdana' color='#000080'>$noreg</font><font size='1'>&nbsp;</font></td>
      </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1'>
              <p align='right' style='margin-right: 10px'>
				<b>
				<font face='Verdana' size='1'>Nama 
				Lengkap:</font></b></p></td>
              <td width='51%' style='border-style: none; border-width: medium' colspan='4'>
              <font size='1' face='Verdana' color='#000080'>$nama</font></td>
      </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1'>
              <p style='margin-right:10; margin-top:1; margin-bottom:1' align='right'>
				<b><font size='1' face='Verdana'>
              Pilihan Jurusan:</font></b></p></td>
              <td width='51%' style='border-style: none; border-width: medium' colspan='4'>
              <font size='1' face='Verdana' color='#000080'>
              $pilihan_prodi_node->title              
              </font><font size='1'>&nbsp;</font></td>
      </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1'>
              <p align='right' style='margin-right: 10px'>
				<b>
				<font size='1' face='Verdana'>B / R:</font></b></p></td>
              <td width='51%' style='border-style: none; border-width: medium' colspan='4'>
              <font face='Verdana' size='1' color='#000080'>
              Reguler
              </font></td>
      </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1'>
              <p align='right' style='margin-right: 10px; margin-top:1px; margin-bottom:1px'>
				<b>
				<font size='1' face='Verdana'>Sekolah:</font></b></p></td>
              <td width='51%' style='border-style: none; border-width: medium' colspan='4'>
              <font size='1' face='Verdana' color='#000080'>$sekolah  </font></td>
      </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1'>
              <p align='right' style='margin-right: 10px; margin-top:2px; margin-bottom:2px'>
				<font face='Verdana' size='1'><b>Nilai UN Murni:</b></font></p></td>
              <td width='51%' style='border-style: none; border-width: medium' colspan='4'>
              <font size='1' face='Verdana'>   $nilai_un  </font></td>
      </tr>
      <tr>
              <td width='103%' style='border-style:none; border-width:medium; ' height='1' colspan='8'>
        </td>
              </tr>
      <tr>
              <td width='103%' style='border-style: none; border-width: medium' height='1' colspan='8'>
        </td>
              </tr>
      <tr>
              <td width='103%' style='border-style: none; border-width: medium' height='1' colspan='8'>
        </td>
              </tr>
      <tr>
              <td width='18%' style='border-bottom:1px solid #C0C0C0; border-left-style:none; border-left-width:medium; border-right-style:none; border-right-width:medium; border-top-style:none; border-top-width:medium' height='1'>
        <font size='1'>&nbsp;</font></td>
              <td width='85%' style='border-bottom:1px solid #C0C0C0; border-left-style:none; border-left-width:medium; border-right-style:none; border-right-width:medium; border-top-style:none; border-top-width:medium' height='1' colspan='7'>
        <font size='1'>&nbsp;</font></td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1'>
        <font size='1'>&nbsp;</font></td>
              <td width='85%' style='border-style: none; border-width: medium' height='1' colspan='7'>
        <font size='1'>&nbsp;</font></td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right' valign='bottom'>
        <p style='margin-top: 2px; margin-bottom: 2px'><font size='1'>&nbsp;</font></p></td>
              <td width='22%' style='border:1px solid #C0C0C0; ' height='1' colspan='2' align='center' bgcolor='#C0C0C0'>
				<p style='margin-top: 2px; margin-bottom: 2px'><b>
				<font size='1' face='Verdana'>Kelas 1</font></b></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' colspan='2' align='center' bgcolor='#C0C0C0'>
				<p style='margin-top: 2px; margin-bottom: 2px'><b>
				<font size='1' face='Verdana'>Kelas 2</font></b></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' colspan='2' align='center' bgcolor='#C0C0C0'>
				<p style='margin-top: 2px; margin-bottom: 2px'><b>
				<font size='1' face='Verdana'>Kelas 3</font></b></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' bgcolor='#C0C0C0'>
				<p align='center'><b><font size='1' face='Verdana'>Rata-Rata</font></b></p></td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right' valign='bottom'>
        <p style='margin-top: 2px; margin-bottom: 2px'><font size='1'>&nbsp;</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'><b>
				<font size='1' face='Verdana'>smt 1</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'><b>
				<font size='1' face='Verdana'>smt 2</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'><b>
				<font size='1' face='Verdana'>smt 1</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'><b>
				<font size='1' face='Verdana'>smt 2</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'><b>
				<font size='1' face='Verdana'>smt 1</font></b></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>&nbsp;</font></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1'>
				<font size='1'>&nbsp;</font></td>
              </tr>";
    
    $jurusan = $profile['data_sekolah']->field_sekolah_jurusan['und'][0]['value'];  
    
    if($jurusan == 'ipa') {$output .= nilai_ipa($profile['nilai_ipa']);}
    
    if($jurusan == 'ips') {$output .= nilai_ips($profile['nilai_ips']);}
    
    if($jurusan == 'bahasa') {$output .= nilai_bahasa($profile['nilai_bahasa']);}
    
    if($jurusan == 'lain') {$output .= nilai_smk($profile['nilai_smk']);}
    
    
    $lain = $profile['data_lain'];
    $prestasi = isset($lain->field_lain_prestasi['und'][0]['value'])?
            $lain->field_lain_prestasi['und'][0]['value']:'-';
    $organisasi = isset($lain->field_lain_organisasi['und'][0]['value'])?
            $lain->field_lain_organisasi['und'][0]['value']:'-';
    $hobi = isset($lain->field_lain_hobi['und'][0]['value'])?
            $lain->field_lain_hobi['und'][0]['value']:'-';
    $training = isset($lain->field_lain_training['und'][0]['value'])?
            $lain->field_lain_training['und'][0]['value']:'-';
    $bahasa = isset($lain->field_lain_bahasa['und'][0]['value'])?
            $lain->field_lain_bahasa['und'][0]['value']:'-';
    
    $output .=
      "<tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right'>
        &nbsp;</td>
              <td width='11%' style='border-style:none; border-width:medium; ' height='1' align='center'>
				</td>
              <td width='11%' style='border-style:none; border-width:medium; ' height='1' align='center'>
				</td>
              <td width='11%' style='border-style:none; border-width:medium; ' height='1' align='center'>
				</td>
              <td width='11%' style='border-style:none; border-width:medium; ' height='1' align='center'>
				</td>
              <td width='11%' style='border-style:none; border-width:medium; ' height='1' align='center'>
				</td>
              <td width='10%' style='border-style:none; border-width:medium; ' height='1' align='center'>
				</td>
              <td width='21%' style='border-style:none; border-width:medium; ' height='1' align='center'>
        		</td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right' valign='top'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Prestasi:</font></b></p></td>
              <td width='86%' style='border-style:none; border-width:medium; ' height='1' align='left' colspan='7'>
				<font size='1' face='Verdana'>$prestasi</font></td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right' valign='top'>
        <font size='1' face='Verdana'>&nbsp;</font></td>
              <td width='86%' style='border-style:none; border-width:medium; ' height='1' align='left' colspan='7'>
				<font face='Verdana' size='1'>&nbsp;</font></td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right' valign='top'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Pengalaman Organisasi:</font></b></p></td>
              <td width='86%' style='border-style:none; border-width:medium; ' height='1' align='left' colspan='7'>
				<font size='1' face='Verdana'>$organisasi</font></td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right' valign='top'>
        <font size='1'>&nbsp;</font></td>
              <td width='86%' style='border-style:none; border-width:medium; ' height='1' align='left' colspan='7'>
				<font size='1'>&nbsp;</font></td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right' valign='top'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Bahasa yang dikuasai:</font></b></p></td>
              <td width='86%' style='border-style:none; border-width:medium; ' height='1' align='left' colspan='7'>
				<font size='1' face='Verdana'>$bahasa</font></td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right' valign='top'>
        <font face='Verdana' size='1'>&nbsp;</font></td>
              <td width='86%' style='border-style:none; border-width:medium; ' height='1' align='left' colspan='7'>
				<font size='1' face='Verdana'>&nbsp;</font></td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right' valign='top'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Trainning/ Kursus:</font></b></p></td>
              <td width='86%' style='border-style:none; border-width:medium; ' height='1' align='left' colspan='7'>
				<font size='1' face='Verdana'>$training</font></td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right' valign='top'>
        <font face='Verdana' size='1'>&nbsp;</font></td>
              <td width='86%' style='border-style:none; border-width:medium; ' height='1' align='left' colspan='7'>
				<font size='1' face='Verdana'>&nbsp;</font></td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right' valign='top'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Hobi:</font></b></p></td>
              <td width='86%' style='border-style:none; border-width:medium; ' height='1' align='left' colspan='7'>
				<font size='1' face='Verdana'>$hobi</font></td>
              </tr>
      </tbody></table>";
    
    $output .= '</body></html>';
    
    print $output;
}

function cetak_nilai_get_style(){
     $style = '<style>
             @media print{
             .noprint{
               display:none
              }
             }
             </style>';
    
    return $style;
}

function nilai_ipa($nilai){
    $output = '';
    $mtk_11 = isset($nilai->field_nilai_mtk_11['und'][0]['value'])?
            $nilai->field_nilai_mtk_11['und'][0]['value']:0;   
    $mtk_12 = isset($nilai->field_nilai_mtk_12['und'][0]['value'])?
            $nilai->field_nilai_mtk_12['und'][0]['value']:0;
 
    $mtk_21 = isset($nilai->field_nilai_mtk_21['und'][0]['value'])?
            $nilai->field_nilai_mtk_21['und'][0]['value']:0;   
    $mtk_22 = isset($nilai->field_nilai_mtk_22['und'][0]['value'])?
            $nilai->field_nilai_mtk_22['und'][0]['value']:0;
    
    $mtk_31 = isset($nilai->field_nilai_mtk_31['und'][0]['value'])?
            $nilai->field_nilai_mtk_31['und'][0]['value']:0;
    
    $mtk_rata = number_format(($mtk_11 + $mtk_12 + $mtk_21 + $mtk_22 + $mtk_31)/5, 2);
    
    //Nilai MATEMATIKA
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Matematika:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
        </p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font size='1' face='Verdana'>
		$mtk_rata
		</font></p></td>
              </tr>";
    
    $ing_11 = isset($nilai->field_nilai_ing_11['und'][0]['value'])?
            $nilai->field_nilai_ing_11['und'][0]['value']:0;
    $ing_12 = isset($nilai->field_nilai_ing_12['und'][0]['value'])?
            $nilai->field_nilai_ing_12['und'][0]['value']:0;
    
    $ing_21 = isset($nilai->field_nilai_ing_21['und'][0]['value'])?
            $nilai->field_nilai_ing_21['und'][0]['value']:0;
    $ing_22 = isset($nilai->field_nilai_ing_22['und'][0]['value'])?
            $nilai->field_nilai_ing_22['und'][0]['value']:0;
    
    $ing_31 = isset($nilai->field_nilai_ing_31['und'][0]['value'])?
            $nilai->field_nilai_ing_31['und'][0]['value']:0;
    
    $ing_rata = number_format(($ing_11 + $ing_12 + $ing_21 + $ing_22 + $ing_31)/5, 2);
    //Nilai BAHASA INGGRIS
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Bahasa Inggris:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
        </p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <font size='1' face='Verdana'>
        $ing_rata
        </font></td>
              </tr>";
    
    $fis_11 = isset($nilai->field_nilai_fis_11['und'][0]['value'])?
            $nilai->field_nilai_fis_11['und'][0]['value']:0;
    $fis_12 = isset($nilai->field_nilai_fis_12['und'][0]['value'])?
            $nilai->field_nilai_fis_12['und'][0]['value']:0;
    
    $fis_21 = isset($nilai->field_nilai_fis_21['und'][0]['value'])?
            $nilai->field_nilai_fis_21['und'][0]['value']:0;
    $fis_22 = isset($nilai->field_nilai_fis_22['und'][0]['value'])?
            $nilai->field_nilai_fis_22['und'][0]['value']:0;
    
    $fis_31 = isset($nilai->field_nilai_fis_31['und'][0]['value'])?
            $nilai->field_nilai_fis_31['und'][0]['value']:0;
    
    $fis_rata = number_format(($fis_11 + $fis_12 + $fis_21 + $fis_22 + $fis_31)/5, 2);
    //Nilai FISIKA
    $output .=
      "<tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right'>
        		</td>
              <td width='86%' style='border:1px solid #C0C0C0; ' height='1' align='center' colspan='7'>
				&nbsp;</td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right'>
        		</td>
              <td width='86%' style='border:1px solid #C0C0C0; ' height='1' align='center' colspan='7' bgcolor='#C0C0C0'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<b><font size='1' face='Verdana'>JURUSAN IPA</font></b></p></td>
              </tr>
      <tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Fisika:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$fis_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$fis_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$fis_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$fis_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$fis_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
        </p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <font size='1' face='Verdana'>
        $fis_rata
        </font></td>
              </tr>";
    
    $bio_11 = isset($nilai->field_nilai_bio_11['und'][0]['value'])?
            $nilai->field_nilai_bio_11['und'][0]['value']:0;
    $bio_12 = isset($nilai->field_nilai_bio_12['und'][0]['value'])?
            $nilai->field_nilai_bio_12['und'][0]['value']:0;
    
    $bio_21 = isset($nilai->field_nilai_bio_21['und'][0]['value'])?
            $nilai->field_nilai_bio_21['und'][0]['value']:0;
    $bio_22 = isset($nilai->field_nilai_bio_22['und'][0]['value'])?
            $nilai->field_nilai_bio_22['und'][0]['value']:0;
    
    $bio_31 = isset($nilai->field_nilai_bio_31['und'][0]['value'])?
            $nilai->field_nilai_bio_31['und'][0]['value']:0;
    
    $bio_rata = number_format(($bio_11 + $bio_12 + $bio_21 + $bio_22 + $bio_31)/5, 2);
    //Nilai BIOLOGI
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Biologi:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$bio_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$bio_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$bio_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$bio_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$bio_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
        </p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <font size='1' face='Verdana'>
        $bio_rata
        </font></td>
              </tr>";
    
    $kim_11 = isset($nilai->field_nilai_kim_11['und'][0]['value'])?
            $nilai->field_nilai_kim_11['und'][0]['value']:0;
    $kim_12 = isset($nilai->field_nilai_kim_12['und'][0]['value'])?
            $nilai->field_nilai_kim_12['und'][0]['value']:0;
    
    $kim_21 = isset($nilai->field_nilai_kim_21['und'][0]['value'])?
            $nilai->field_nilai_kim_21['und'][0]['value']:0;
    $kim_22 = isset($nilai->field_nilai_kim_22['und'][0]['value'])?
            $nilai->field_nilai_kim_22['und'][0]['value']:0;
    
    $kim_31 = isset($nilai->field_nilai_kim_31['und'][0]['value'])?
            $nilai->field_nilai_kim_31['und'][0]['value']:0;
    
    $kim_rata = number_format(($kim_11 + $kim_12 + $kim_21 + $kim_22 + $kim_31)/5, 2);
    //Nilai KIMIA
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Kimia:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$kim_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$kim_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$kim_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$kim_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>$kim_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
        </p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <font size='1' face='Verdana'>
        $kim_rata
        </font></td>
              </tr>";
    
    $rata_all = number_format(($mtk_rata + $ing_rata + $fis_rata + $bio_rata + $kim_rata)/5, 2);
    //Nilai RATA2
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>RATA-RATA:</font></b></p></td>
              <td colspan='6' width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>-</font></p></td>             
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <font size='1' face='Verdana'>
        <b>$rata_all</b>
        </font></td>
              </tr>";
    
    return $output;
}

function nilai_ips($nilai){
    $output = '';
    
    $mtk_11 = isset($nilai->field_nilai_ips_mtk_11['und'][0]['value'])?
            $nilai->field_nilai_ips_mtk_11['und'][0]['value']:0;
    $mtk_12 = isset($nilai->field_nilai_ips_mtk_12['und'][0]['value'])?
            $nilai->field_nilai_ips_mtk_12['und'][0]['value']:0;
    
    $mtk_21 = isset($nilai->field_nilai_ips_mtk_21['und'][0]['value'])?
            $nilai->field_nilai_ips_mtk_21['und'][0]['value']:0;
    $mtk_22 = isset($nilai->field_nilai_ips_mtk_22['und'][0]['value'])?
            $nilai->field_nilai_ips_mtk_22['und'][0]['value']:0;
    
    $mtk_31 = isset($nilai->field_nilai_ips_mtk_31['und'][0]['value'])?
            $nilai->field_nilai_ips_mtk_31['und'][0]['value']:0;
    
    $mtk_rata = number_format(($mtk_11 + $mtk_12 + $mtk_21 + $mtk_22 + $mtk_31)/5, 2);
    
    //Nilai MATEMATIKA
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Matematika:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
        </p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font size='1' face='Verdana'>
		$mtk_rata
		</font></p></td>
              </tr>";
    
    $ing_11 = isset($nilai->field_nilai_ips_ing_11['und'][0]['value'])?
            $nilai->field_nilai_ips_ing_11['und'][0]['value']:0;
    $ing_12 = isset($nilai->field_nilai_ips_ing_12['und'][0]['value'])?
            $nilai->field_nilai_ips_ing_12['und'][0]['value']:0;
    
    $ing_21 = isset($nilai->field_nilai_ips_ing_21['und'][0]['value'])?
            $nilai->field_nilai_ips_ing_21['und'][0]['value']:0;
    $ing_22 = isset($nilai->field_nilai_ips_ing_22['und'][0]['value'])?
            $nilai->field_nilai_ips_ing_22['und'][0]['value']:0;
    
    $ing_31 = isset($nilai->field_nilai_ips_ing_31['und'][0]['value'])?
            $nilai->field_nilai_ips_ing_31['und'][0]['value']:0;
    
    $ing_rata = number_format(($ing_11 + $ing_12 + $ing_21 + $ing_22 + $ing_31)/5, 2);
    //Nilai BAHASA INGGRIS
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Bahasa Inggris:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
        </p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <font size='1' face='Verdana'>
        $ing_rata
        </font></td>
              </tr>";
      
    //Nilai IPS
    $output .=
      "<tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right'>
        		</td>
              <td width='86%' style='border:1px solid #C0C0C0; ' height='1' align='center' colspan='7'>
				&nbsp;</td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right'>
        <font size='1'>&nbsp;</font></td>
              <td width='86%' style='border:1px solid #C0C0C0; ' height='1' align='center' colspan='7' bgcolor='#C0C0C0'>
				<p style='margin-top: 2px; margin-bottom: 2px'><b>
				<font size='1' face='Verdana'>JURUSAN IPS</font></b></p></td>
              </tr>";
    
    
    $eko_11 = isset($nilai->field_nilai_ips_eko_11['und'][0]['value'])?
            $nilai->field_nilai_ips_eko_11['und'][0]['value']:0;
    $eko_12 = isset($nilai->field_nilai_ips_eko_12['und'][0]['value'])?
            $nilai->field_nilai_ips_eko_12['und'][0]['value']:0;
    
    $eko_21 = isset($nilai->field_nilai_ips_eko_21['und'][0]['value'])?
            $nilai->field_nilai_ips_eko_21['und'][0]['value']:0;
    $eko_22 = isset($nilai->field_nilai_ips_eko_22['und'][0]['value'])?
            $nilai->field_nilai_ips_eko_22['und'][0]['value']:0;
    
    $eko_31 = isset($nilai->field_nilai_ips_eko_31['und'][0]['value'])?
            $nilai->field_nilai_ips_eko_31['und'][0]['value']:0;
    
    $eko_rata = number_format(($eko_11 + $eko_12 + $eko_21 + $eko_22 + $eko_31)/5, 2);
    //Nilai EKONOMI
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Ekonomi:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$eko_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$eko_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$eko_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$eko_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$eko_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>
				&nbsp;</font></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font face='Verdana' size='1'>
		$eko_rata		
		</font></p></td>
              </tr>";
    
    $sos_11 = isset($nilai->field_nilai_ips_sos_11['und'][0]['value'])?
            $nilai->field_nilai_ips_sos_11['und'][0]['value']:0;
    $sos_12 = isset($nilai->field_nilai_ips_sos_12['und'][0]['value'])?
            $nilai->field_nilai_ips_sos_12['und'][0]['value']:0;
    
    $sos_21 = isset($nilai->field_nilai_ips_sos_21['und'][0]['value'])?
            $nilai->field_nilai_ips_sos_21['und'][0]['value']:0;
    $sos_22 = isset($nilai->field_nilai_ips_sos_22['und'][0]['value'])?
            $nilai->field_nilai_ips_sos_22['und'][0]['value']:0;
    
    $sos_31 = isset($nilai->field_nilai_ips_sos_31['und'][0]['value'])?
            $nilai->field_nilai_ips_sos_31['und'][0]['value']:0;
    
    $sos_rata = number_format(($sos_11 + $sos_12 + $sos_21 + $sos_22 + $sos_31)/5, 2);
    //Nilai SOSIOLOGI
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Sosioloagi:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$sos_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$sos_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$sos_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$sos_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$sos_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>

				&nbsp;</font></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font face='Verdana' size='1'>
		$sos_rata				
		</font></p></td>
              </tr>";
    
    $geo_11 = isset($nilai->field_nilai_ips_geo_11['und'][0]['value'])?
            $nilai->field_nilai_ips_geo_11['und'][0]['value']:0;
    $geo_12 = isset($nilai->field_nilai_ips_geo_12['und'][0]['value'])?
            $nilai->field_nilai_ips_geo_12['und'][0]['value']:0;
    
    $geo_21 = isset($nilai->field_nilai_ips_geo_21['und'][0]['value'])?
            $nilai->field_nilai_ips_geo_21['und'][0]['value']:0;
    $geo_22 = isset($nilai->field_nilai_ips_geo_22['und'][0]['value'])?
            $nilai->field_nilai_ips_geo_22['und'][0]['value']:0;
    
    $geo_31 = isset($nilai->field_nilai_ips_geo_31['und'][0]['value'])?
            $nilai->field_nilai_ips_geo_31['und'][0]['value']:0;
    
    $geo_rata = number_format(($geo_11 + $geo_12 + $geo_21 + $geo_22 + $geo_31)/5, 2);
    //Nilai GEOGRAFI
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Geografi:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$geo_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$geo_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$geo_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$geo_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$geo_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>

				&nbsp;</font></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font face='Verdana' size='1'>
		$geo_rata				
		</font></p></td>
              </tr>";
    
    $rata_all = number_format(($mtk_rata + $ing_rata + $sos_rata + $eko_rata + $geo_rata)/5, 2);
    //Nilai RATA2
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>RATA-RATA:</font></b></p></td>
              <td colspan='6' width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>-</font></p></td>             
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <font size='1' face='Verdana'>
        <b>$rata_all</b>
        </font></td>
              </tr>";
    
    return $output;
}


function nilai_bahasa($nilai){
    $output = '';
    
    $mtk_11 = isset($nilai->field_nilai_bhs_mtk_11['und'][0]['value'])?
            $nilai->field_nilai_bhs_mtk_11['und'][0]['value']:0;
    $mtk_12 = isset($nilai->field_nilai_bhs_mtk_12['und'][0]['value'])?
            $nilai->field_nilai_bhs_mtk_12['und'][0]['value']:0;
    
    $mtk_21 = isset($nilai->field_nilai_bhs_mtk_21['und'][0]['value'])?
            $nilai->field_nilai_bhs_mtk_21['und'][0]['value']:0;
    $mtk_22 = isset($nilai->field_nilai_bhs_mtk_22['und'][0]['value'])?
            $nilai->field_nilai_bhs_mtk_22['und'][0]['value']:0;
    
    $mtk_31 = isset($nilai->field_nilai_bhs_mtk_31['und'][0]['value'])?
            $nilai->field_nilai_bhs_mtk_31['und'][0]['value']:0;
    
    $mtk_rata = number_format(($mtk_11 + $mtk_12 + $mtk_21 + $mtk_22 + $mtk_31)/5, 2);
    
    //Nilai MATEMATIKA
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Matematika:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
        </p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font size='1' face='Verdana'>
		$mtk_rata
		</font></p></td>
              </tr>";
    
    $ing_11 = isset($nilai->field_nilai_bhs_ing_11['und'][0]['value'])?
            $nilai->field_nilai_bhs_ing_11['und'][0]['value']:0;
    $ing_12 = isset($nilai->field_nilai_bhs_ing_12['und'][0]['value'])?
            $nilai->field_nilai_bhs_ing_12['und'][0]['value']:0;
    
    $ing_21 = isset($nilai->field_nilai_bhs_ing_21['und'][0]['value'])?
            $nilai->field_nilai_bhs_ing_21['und'][0]['value']:0;
    $ing_22 = isset($nilai->field_nilai_bhs_ing_22['und'][0]['value'])?
            $nilai->field_nilai_bhs_ing_22['und'][0]['value']:0;
    
    $ing_31 = isset($nilai->field_nilai_bhs_ing_31['und'][0]['value'])?
            $nilai->field_nilai_bhs_ing_31['und'][0]['value']:0;
    
    $ing_rata = number_format(($ing_11 + $ing_12 + $ing_21 + $ing_22 + $ing_31)/5, 2);
    //Nilai BAHASA INGGRIS
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Bahasa Inggris:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
        </p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <font size='1' face='Verdana'>
        $ing_rata
        </font></td>
              </tr>";
      
    //Nilai IPS
    $output .=
      "<tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right'>
        		</td>
              <td width='86%' style='border:1px solid #C0C0C0; ' height='1' align='center' colspan='7'>
				&nbsp;</td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right'>
        <font size='1'>&nbsp;</font></td>
              <td width='86%' style='border:1px solid #C0C0C0; ' height='1' align='center' colspan='7' bgcolor='#C0C0C0'>
				<p style='margin-top: 2px; margin-bottom: 2px'><b>
				<font size='1' face='Verdana'>JURUSAN IPS</font></b></p></td>
              </tr>";
    
    
    $nama_mapel1 = isset($nilai->field_nilai_bhs_mapel1_nama['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel1_nama['und'][0]['value']:'Mata Pelajaran 1';
    $mapel1_11 = isset($nilai->field_nilai_bhs_mapel1_11['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel1_11['und'][0]['value']:0;
    $mapel1_12 = isset($nilai->field_nilai_bhs_mapel1_12['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel1_12['und'][0]['value']:0;
    
    $mapel1_21 = isset($nilai->field_nilai_bhs_mapel1_21['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel1_21['und'][0]['value']:0;
    $mapel1_22 = isset($nilai->field_nilai_bhs_mapel1_22['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel1_22['und'][0]['value']:0;
    
    $mapel1_31 = isset($nilai->field_nilai_bhs_mapel1_31['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel1_31['und'][0]['value']:0;
    
    $mapel1_rata = number_format(($mapel1_11 + $mapel1_12 + $mapel1_21 + $mapel1_22 + $mapel1_31)/5, 2);
    //Nilai EKONOMI
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>$nama_mapel1:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel1_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel1_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel1_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel1_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel1_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>
				&nbsp;</font></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font face='Verdana' size='1'>
		$mapel1_rata		
		</font></p></td>
              </tr>";
    
    $nama_mapel2 = isset($nilai->field_nilai_bhs_mapel2_nama['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel2_nama['und'][0]['value']:'Mata Pelajaran 2';
    $mapel2_11 = isset($nilai->field_nilai_bhs_mapel2_11['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel2_11['und'][0]['value']:0;
    $mapel2_12 = isset($nilai->field_nilai_bhs_mapel2_12['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel2_12['und'][0]['value']:0;
    
    $mapel2_21 = isset($nilai->field_nilai_bhs_mapel2_21['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel2_21['und'][0]['value']:0;
    $mapel2_22 = isset($nilai->field_nilai_bhs_mapel2_22['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel2_22['und'][0]['value']:0;
    
    $mapel2_31 = isset($nilai->field_nilai_bhs_mapel2_31['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel2_31['und'][0]['value']:0;
    
    $mapel2_rata = number_format(($mapel2_11 + $mapel2_12 + $mapel2_21 + $mapel2_22 + $mapel2_31)/5, 2);
    //Nilai SOSIOLOGI
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>$nama_mapel2:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel2_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel2_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel2_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel2_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel2_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>

				&nbsp;</font></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font face='Verdana' size='1'>
		$mapel2_rata				
		</font></p></td>
              </tr>";
    
    $nama_mapel3 = isset($nilai->field_nilai_bhs_mapel3_nama['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel3_nama['und'][0]['value']:'Mata Pelajaran 3';
    $mapel3_11 = isset($nilai->field_nilai_bhs_mapel3_11['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel3_11['und'][0]['value']:0;
    $mapel3_12 = isset($nilai->field_nilai_bhs_mapel3_12['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel3_12['und'][0]['value']:0;
    
    $mapel3_21 = isset($nilai->field_nilai_bhs_mapel3_21['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel3_21['und'][0]['value']:0;
    $mapel3_22 = isset($nilai->field_nilai_bhs_mapel3_22['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel3_22['und'][0]['value']:0;
    
    $mapel3_31 = isset($nilai->field_nilai_bhs_mapel3_31['und'][0]['value'])?
            $nilai->field_nilai_bhs_mapel3_31['und'][0]['value']:0;
    
    $mapel3_rata = number_format(($mapel3_11 + $mapel3_12 + $mapel3_21 + $mapel3_22 + $mapel3_31)/5, 2);
    //Nilai GEOGRAFI
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>$nama_mapel3:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel3_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel3_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel3_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel3_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel3_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>

				&nbsp;</font></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font face='Verdana' size='1'>
		$mapel3_rata				
		</font></p></td>
              </tr>";
    
    $rata_all = number_format(($mtk_rata + $ing_rata + $mapel1_rata + $mapel2_rata + $mapel3_rata)/5, 2);
    //Nilai RATA2
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>RATA-RATA:</font></b></p></td>
              <td colspan='6' width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>-</font></p></td>             
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <font size='1' face='Verdana'>
        <b>$rata_all</b>
        </font></td>
              </tr>";
    
    return $output;
}


function nilai_smk($nilai){
    $output = '';
    
    $mtk_11 = isset($nilai->field_nilai_smk_mtk_11['und'][0]['value'])?
            $nilai->field_nilai_smk_mtk_11['und'][0]['value']:0;
    $mtk_12 = isset($nilai->field_nilai_smk_mtk_12['und'][0]['value'])?
            $nilai->field_nilai_smk_mtk_12['und'][0]['value']:0;
    
    $mtk_21 = isset($nilai->field_nilai_smk_mtk_21['und'][0]['value'])?
            $nilai->field_nilai_smk_mtk_21['und'][0]['value']:0;
    $mtk_22 = isset($nilai->field_nilai_smk_mtk_22['und'][0]['value'])?
            $nilai->field_nilai_smk_mtk_22['und'][0]['value']:0;
    
    $mtk_31 = isset($nilai->field_nilai_smk_mtk_31['und'][0]['value'])?
            $nilai->field_nilai_smk_mtk_31['und'][0]['value']:0;
    
    $mtk_rata = number_format(($mtk_11 + $mtk_12 + $mtk_21 + $mtk_22 + $mtk_31)/5, 2);
    
    //Nilai MATEMATIKA
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Matematika:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mtk_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
        </p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font size='1' face='Verdana'>
		$mtk_rata
		</font></p></td>
              </tr>";
    
    $ing_11 = isset($nilai->field_nilai_smk_ing_11['und'][0]['value'])?
            $nilai->field_nilai_smk_ing_11['und'][0]['value']:0;
    $ing_12 = isset($nilai->field_nilai_smk_ing_12['und'][0]['value'])?
            $nilai->field_nilai_smk_ing_12['und'][0]['value']:0;
    
    $ing_21 = isset($nilai->field_nilai_smk_ing_21['und'][0]['value'])?
            $nilai->field_nilai_smk_ing_21['und'][0]['value']:0;
    $ing_22 = isset($nilai->field_nilai_smk_ing_22['und'][0]['value'])?
            $nilai->field_nilai_smk_ing_22['und'][0]['value']:0;
    
    $ing_31 = isset($nilai->field_nilai_smk_ing_31['und'][0]['value'])?
            $nilai->field_nilai_smk_ing_31['und'][0]['value']:0;
    
    $ing_rata = number_format(($ing_11 + $ing_12 + $ing_21 + $ing_22 + $ing_31)/5, 2);
    //Nilai BAHASA INGGRIS
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>Bahasa Inggris:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$ing_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
        </p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <font size='1' face='Verdana'>
        $ing_rata
        </font></td>
              </tr>";
      
    //Nilai IPS
    $output .=
      "<tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right'>
        		</td>
              <td width='86%' style='border:1px solid #C0C0C0; ' height='1' align='center' colspan='7'>
				&nbsp;</td>
              </tr>
      <tr>
              <td width='18%' style='border-style: none; border-width: medium' height='1' align='right'>
        <font size='1'>&nbsp;</font></td>
              <td width='86%' style='border:1px solid #C0C0C0; ' height='1' align='center' colspan='7' bgcolor='#C0C0C0'>
				<p style='margin-top: 2px; margin-bottom: 2px'><b>
				<font size='1' face='Verdana'>JURUSAN IPS</font></b></p></td>
              </tr>";
    
    
    $nama_mapel1 = isset($nilai->field_nilai_smk_mapel1_nama['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel1_nama['und'][0]['value']:'Mata Pelajaran 1';
    $mapel1_11 = isset($nilai->field_nilai_smk_mapel1_11['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel1_11['und'][0]['value']:0;
    $mapel1_12 = isset($nilai->field_nilai_smk_mapel1_12['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel1_12['und'][0]['value']:0;
    
    $mapel1_21 = isset($nilai->field_nilai_smk_mapel1_21['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel1_21['und'][0]['value']:0;
    $mapel1_22 = isset($nilai->field_nilai_smk_mapel1_22['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel1_22['und'][0]['value']:0;
    
    $mapel1_31 = isset($nilai->field_nilai_smk_mapel1_31['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel1_31['und'][0]['value']:0;
    
    $mapel1_rata = number_format(($mapel1_11 + $mapel1_12 + $mapel1_21 + $mapel1_22 + $mapel1_31)/5, 2);
    //Nilai EKONOMI
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>$nama_mapel1:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel1_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel1_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel1_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel1_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel1_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>
				&nbsp;</font></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font face='Verdana' size='1'>
		$mapel1_rata		
		</font></p></td>
              </tr>";
    
    $nama_mapel2 = isset($nilai->field_nilai_smk_mapel2_nama['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel2_nama['und'][0]['value']:'Mata Pelajaran 2';
    $mapel2_11 = isset($nilai->field_nilai_smk_mapel2_11['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel2_11['und'][0]['value']:0;
    $mapel2_12 = isset($nilai->field_nilai_smk_mapel2_12['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel2_12['und'][0]['value']:0;
    
    $mapel2_21 = isset($nilai->field_nilai_smk_mapel2_21['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel2_21['und'][0]['value']:0;
    $mapel2_22 = isset($nilai->field_nilai_smk_mapel2_22['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel2_22['und'][0]['value']:0;
    
    $mapel2_31 = isset($nilai->field_nilai_smk_mapel2_31['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel2_31['und'][0]['value']:0;
    
    $mapel2_rata = number_format(($mapel2_11 + $mapel2_12 + $mapel2_21 + $mapel2_22 + $mapel2_31)/5, 2);
    //Nilai SOSIOLOGI
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>$nama_mapel2:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel2_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel2_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel2_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel2_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel2_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>

				&nbsp;</font></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font face='Verdana' size='1'>
		$mapel2_rata				
		</font></p></td>
              </tr>";
    
    $nama_mapel3 = isset($nilai->field_nilai_smk_mapel3_nama['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel3_nama['und'][0]['value']:'Mata Pelajaran 3';
    $mapel3_11 = isset($nilai->field_nilai_smk_mapel3_11['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel3_11['und'][0]['value']:0;
    $mapel3_12 = isset($nilai->field_nilai_smk_mapel3_12['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel3_12['und'][0]['value']:0;
    
    $mapel3_21 = isset($nilai->field_nilai_smk_mapel3_21['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel3_21['und'][0]['value']:0;
    $mapel3_22 = isset($nilai->field_nilai_smk_mapel3_22['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel3_22['und'][0]['value']:0;
    
    $mapel3_31 = isset($nilai->field_nilai_smk_mapel3_31['und'][0]['value'])?
            $nilai->field_nilai_smk_mapel3_31['und'][0]['value']:0;
    
    $mapel3_rata = number_format(($mapel3_11 + $mapel3_12 + $mapel3_21 + $mapel3_22 + $mapel3_31)/5, 2);
    //Nilai GEOGRAFI
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>$nama_mapel3:</font></b></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel3_11</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel3_12</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel3_21</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel3_22</font></p></td>
              <td width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>$mapel3_31</font></p></td>
              <td width='10%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font face='Verdana' size='1'>

				&nbsp;</font></p></td>
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <p style='margin-top: 2px; margin-bottom: 2px'>
		<font face='Verdana' size='1'>
		$mapel3_rata				
		</font></p></td>
              </tr>";
    
    $rata_all = number_format(($mtk_rata + $ing_rata + $mapel1_rata + $mapel2_rata + $mapel3_rata)/5, 2);
    //Nilai RATA2
    $output .=
      "<tr>
              <td width='18%' style='border:1px solid #C0C0C0; ' height='1' align='right'>
        <p style='margin-right: 10px; margin-top: 2px; margin-bottom: 2px'><b>
		<font size='1' face='Verdana'>RATA-RATA:</font></b></p></td>
              <td colspan='6' width='11%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
				<p style='margin-top: 2px; margin-bottom: 2px'>
				<font size='1' face='Verdana'>-</font></p></td>             
              <td width='21%' style='border:1px solid #C0C0C0; ' height='1' align='center'>
        <font size='1' face='Verdana'>
        <b>$rata_all</b>
        </font></td>
              </tr>";
    
    return $output;
}