<?php


function admission_konfirmasi_export(){
    global $user;
       
    // Produce excel file..
  include_once libraries_get_path('phpexcel') . '/Classes/PHPExcel.php';

  $fname_date = 'daftar-konfirmasi-pembayaran';
  
  $fname_ext = "xlsx";

  $output_path = variable_get('file_public_path', conf_path() . '/files')
      . "/" . $fname_date . "_" . $user->uid . "." . $fname_ext;
  // uid pada nama file untuk mengantisipasi multi user yg mendownlod pada waktu bersamaan
  // Create new PHPExcel object
  $objPHPExcel = new PHPExcel();

  $objPHPExcel->getProperties()->setCreator($user->name)
      ->setLastModifiedBy($user->name)
      ->setTitle("Laporan Konfirmasi Pembayaran Mahasiswa")
      ->setSubject("Laporan Konfirmasi Pembayaran Mahasiswa")
      ->setDescription("Laporan Konfirmasi Pembayaran Mahasiswa")
      ->setKeywords("Laporan Konfirmasi Pembayaran Mahasiswa")
      ->setCategory("Laporan Pembayaran");
  
  
    $pembayaran_array = node_load_multiple(array(), array('type' => 'pembayaran'));

  // SHEET 0
  $objPHPExcel->setActiveSheetIndex(0);
  
  // SET WIDTH
  $objPHPExcel->getActiveSheet()->getColumnDimension('A')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('B')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('C')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('D')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('E')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('F')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('G')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('H')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('I')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('J')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('K')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('L')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('M')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('N')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('O')->setAutoSize(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('A1', 'NO. ');
  $objPHPExcel->getActiveSheet()->getStyle('A1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('A1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('B1', 'NAMA');
  $objPHPExcel->getActiveSheet()->getStyle('B1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('B1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('C1', 'ASAL SEKOLAH');
  $objPHPExcel->getActiveSheet()->getStyle('C1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('C1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('D1', 'KOTA');
  $objPHPExcel->getActiveSheet()->getStyle('D1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('D1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('E1', 'TELEPON');
  $objPHPExcel->getActiveSheet()->getStyle('E1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('E1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('F1', 'HP');
  $objPHPExcel->getActiveSheet()->getStyle('F1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('F1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('G1', 'EMAIL');
  $objPHPExcel->getActiveSheet()->getStyle('G1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('G1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('H1', 'TGL BAYAR SETORAN');
  $objPHPExcel->getActiveSheet()->getStyle('H1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('H1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('I1', 'SETORAN');
  $objPHPExcel->getActiveSheet()->getStyle('I1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('I1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('J1', 'KE BANK');
  $objPHPExcel->getActiveSheet()->getStyle('J1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('J1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('K1', 'DARI BANK');
  $objPHPExcel->getActiveSheet()->getStyle('K1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('K1')->getFont()->setBold(true);
  
   $objPHPExcel->getActiveSheet()->setCellValue('L1', 'NO.REK.');
  $objPHPExcel->getActiveSheet()->getStyle('L1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('L1')->getFont()->setBold(true);
  
   $objPHPExcel->getActiveSheet()->setCellValue('M1', 'A/N');
  $objPHPExcel->getActiveSheet()->getStyle('M1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('M1')->getFont()->setBold(true);
  
   $objPHPExcel->getActiveSheet()->setCellValue('N1', 'CATATAN');
  $objPHPExcel->getActiveSheet()->getStyle('N1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('N1')->getFont()->setBold(true);
  
   $objPHPExcel->getActiveSheet()->setCellValue('O1', 'TGL KONFIRMASI');
  $objPHPExcel->getActiveSheet()->getStyle('O1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('O1')->getFont()->setBold(true);
  
    
  $i = 1;
  $row = 2;
  foreach($pembayaran_array as $pembayaran_node){
      
      $reg_node = node_load($pembayaran_node->field_bayar_noreg['und'][0]['target_id']);
      $user_load = user_load($reg_node->field_reg_candidate['und'][0]['target_id']);
      $profile_user = profile2_load_by_user($user_load->uid);
      
      $nama = $profile_user['data_pribadi']->field_personal_fullname['und'][0]['value'];
      $tipe_sekolah = $profile_user['data_sekolah']->field_sekolah_tipe['und'][0]['value'];
      $nama_sekolah = $profile_user['data_sekolah']->field_sekolah_sma['und'][0]['value'];
      $asal_sekolah = $tipe_sekolah.' '.$nama_sekolah;
      $kota_nid = $profile_user['data_pribadi']->field_personal_city['und'][0]['target_id'];
      $kota_node = node_load($kota_nid);
      $kota = $kota_node->title;
      
      $telp = $profile_user['data_pribadi']->field_personal_telp['und'][0]['value'];
      $telp = empty($telp)? ' - ':$telp;
      
      $hp = $profile_user['data_pribadi']->field_personal_hp['und'][0]['value'];
      $email = $user_load->mail;
      $tanggal_bayar = $pembayaran_node->field_bayar_tanggal['und'][0]['value'];
      $tanggal = date('d M Y',  strtotime($tanggal_bayar));
      $cara_bayar = $pembayaran_node->field_bayar_cara['und'][0]['value'];
      $bank_tujuan = $pembayaran_node->field_bayar_bank_penerima['und'][0]['value'];
      $bank_pengirim = $pembayaran_node->field_bayar_bank_pengirim['und'][0]['value'];
      $rekening_pengirim = $pembayaran_node->field_bayar_rekening['und'][0]['value'];
      $nama_pengirim = $pembayaran_node->field_bayar_pengirim['und'][0]['value'];
      
      $catatan = isset($pembayaran_node->field_bayar_catatan['und'][0]['value'])?
              $pembayaran_node->field_bayar_catatan['und'][0]['value']:'-';     
      
      $tanggal_konfirmasi = date('d M Y',$pembayaran_node->created);
      
      $objPHPExcel->getActiveSheet()->setCellValue('A'.$row, $i);
        $objPHPExcel->getActiveSheet()->getStyle('A'.$row)->getFont()->setSize(12);

        $objPHPExcel->getActiveSheet()->setCellValue('B'.$row, $nama);
        $objPHPExcel->getActiveSheet()->getStyle('B'.$row)->getFont()->setSize(12);

        $objPHPExcel->getActiveSheet()->setCellValue('C'.$row, $asal_sekolah);
        $objPHPExcel->getActiveSheet()->getStyle('C'.$row)->getFont()->setSize(12);

        $objPHPExcel->getActiveSheet()->setCellValue('D'.$row, $kota);
        $objPHPExcel->getActiveSheet()->getStyle('D'.$row)->getFont()->setSize(12);

        $objPHPExcel->getActiveSheet()->setCellValue('E'.$row, $telp);
        $objPHPExcel->getActiveSheet()->getStyle('E'.$row)->getFont()->setSize(12);
        //set 'text' agar angka 0 tampil di layar
        $objPHPExcel->getActiveSheet()->setCellValueExplicit('E'.$row, $hp, PHPExcel_Cell_DataType::TYPE_STRING);

        $objPHPExcel->getActiveSheet()->setCellValue('F'.$row, $hp);
        $objPHPExcel->getActiveSheet()->getStyle('F'.$row)->getFont()->setSize(12);
        //set 'text' agar angka 0 tampil di layar
        $objPHPExcel->getActiveSheet()->setCellValueExplicit('F'.$row, $hp, PHPExcel_Cell_DataType::TYPE_STRING);

        $objPHPExcel->getActiveSheet()->setCellValue('G'.$row, $email);
        $objPHPExcel->getActiveSheet()->getStyle('G'.$row)->getFont()->setSize(12);

        $objPHPExcel->getActiveSheet()->setCellValue('H'.$row, $tanggal);
        $objPHPExcel->getActiveSheet()->getStyle('H'.$row)->getFont()->setSize(12);

        $objPHPExcel->getActiveSheet()->setCellValue('I'.$row, strtoupper($cara_bayar));
        $objPHPExcel->getActiveSheet()->getStyle('I'.$row)->getFont()->setSize(12);

        $objPHPExcel->getActiveSheet()->setCellValue('J'.$row, $bank_tujuan);
        $objPHPExcel->getActiveSheet()->getStyle('J'.$row)->getFont()->setSize(12);

        $objPHPExcel->getActiveSheet()->setCellValue('K'.$row, $bank_pengirim);
        $objPHPExcel->getActiveSheet()->getStyle('K'.$row)->getFont()->setSize(12);

         $objPHPExcel->getActiveSheet()->setCellValue('L'.$row, $rekening_pengirim);
        $objPHPExcel->getActiveSheet()->getStyle('L'.$row)->getFont()->setSize(12);

         $objPHPExcel->getActiveSheet()->setCellValue('M'.$row, $nama_pengirim);
        $objPHPExcel->getActiveSheet()->getStyle('M'.$row)->getFont()->setSize(12);

         $objPHPExcel->getActiveSheet()->setCellValue('N'.$row, $catatan);
        $objPHPExcel->getActiveSheet()->getStyle('N'.$row)->getFont()->setSize(12);

         $objPHPExcel->getActiveSheet()->setCellValue('O'.$row, $tanggal_konfirmasi);
        $objPHPExcel->getActiveSheet()->getStyle('O'.$row)->getFont()->setSize(12);

        $row++;
        $i++;
  }

  // Naming worksheet 1
  $objPHPExcel->getActiveSheet()->setTitle('Daftar Konfirmasi Pembayaran');

  // Set active sheet index to the first sheet, so Excel opens this as the first sheet
  $objPHPExcel->setActiveSheetIndex(0);

  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel2007');
  $objWriter->save($output_path);

  //dpm($output_path, 'output_path');


  header('Content-Description: File Transfer');
  header('Content-Type: application/octet-stream');
  header('Content-Disposition: attachment; filename=' . $fname_date . "." . $fname_ext);
  header('Content-Transfer-Encoding: binary');
  header('Expires: 0');
  header('Cache-Control: must-revalidate');
  header('Pragma: public');
  header('Content-Length: ' . filesize($output_path));
  ob_clean();
  flush();
  readfile($output_path);

  unlink($output_path);

  exit;
}
